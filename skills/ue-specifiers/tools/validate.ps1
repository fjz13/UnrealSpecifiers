param(
    [int]$ExpectedSourceCount = 447,
    [int]$ExpectedCommonRows = 93,
    [int]$ExpectedConstraintRows = 42,
    [int]$ExpectedAmbiguousRows = 82
)

$ErrorActionPreference = "Stop"

$SkillRoot = (Resolve-Path (Join-Path $PSScriptRoot "..")).Path
$RepoRoot = (Resolve-Path (Join-Path $SkillRoot "..\..")).Path
$SourceRoot = Join-Path $SkillRoot "references\sources"
$IndexRoot = Join-Path $SkillRoot "references\indexes"
$CategoryIndexRoot = Join-Path $IndexRoot "sources"
$ThisScript = $MyInvocation.MyCommand.Path

$Failures = New-Object System.Collections.Generic.List[string]

function Add-Failure {
    param([string]$Message)
    $Failures.Add($Message) | Out-Null
}

function Get-MarkdownText {
    param([string]$Path)
    return [System.IO.File]::ReadAllText($Path, [System.Text.Encoding]::UTF8)
}

function Get-TableRows {
    param([string]$Path)
    Get-Content -Path $Path | Where-Object {
        $_ -match "^\|" -and
        $_ -notmatch "^\|\s*-+" -and
        $_ -notmatch "^\|\s*(ID|Symbol|Concern|Category)\s*\|"
    }
}

function Get-Cell {
    param(
        [string]$Row,
        [int]$Index
    )
    $cells = $Row -split "\|"
    if ($cells.Count -le $Index) {
        return $null
    }
    return $cells[$Index].Trim()
}

function Unwrap-CodeCell {
    param([string]$Cell)
    if ($null -eq $Cell) {
        return $null
    }
    if ($Cell -match '^`(.+)`$') {
        return $Matches[1]
    }
    return $Cell
}

function Test-SourceDocPath {
    param(
        [string]$RelativePath,
        [string]$Context
    )
    if ([string]::IsNullOrWhiteSpace($RelativePath)) {
        Add-Failure "$Context has an empty Doc path."
        return
    }

    $resolved = Join-Path $SourceRoot $RelativePath
    if (-not (Test-Path -Path $resolved -PathType Leaf)) {
        Add-Failure "$Context points to missing source doc: $RelativePath"
    }
}

function Test-IndexDocTable {
    param(
        [string]$Path,
        [int]$ExpectedRows,
        [string]$Label
    )

    $rows = Get-TableRows -Path $Path
    if ($rows.Count -ne $ExpectedRows) {
        Add-Failure "$Label row count is $($rows.Count), expected $ExpectedRows."
    }

    foreach ($row in $rows) {
        $id = Unwrap-CodeCell (Get-Cell -Row $row -Index 1)
        $doc = Unwrap-CodeCell (Get-Cell -Row $row -Index 4)
        Test-SourceDocPath -RelativePath $doc -Context "$Label row '$id'"
    }

    return $rows.Count
}

function Test-CategoryIndexDocTables {
    $totalRows = 0

    foreach ($indexFile in Get-ChildItem -Path $CategoryIndexRoot -Filter "*.index.md" | Sort-Object Name) {
        $docRoot = $null
        $seenIds = @{}

        foreach ($line in Get-Content -Path $indexFile.FullName) {
            if ($line -match '^> Doc root:\s*`(.+)`') {
                $docRoot = $Matches[1]
                continue
            }

            if ($line -notmatch '^\|\s*`') {
                continue
            }

            $id = Unwrap-CodeCell (Get-Cell -Row $line -Index 1)
            $doc = Unwrap-CodeCell (Get-Cell -Row $line -Index 4)
            $totalRows += 1

            if ([string]::IsNullOrWhiteSpace($docRoot)) {
                Add-Failure "$($indexFile.Name) row '$id' appears before a Doc root."
                continue
            }

            if ($seenIds.ContainsKey($id)) {
                Add-Failure "$($indexFile.Name) has duplicate ID '$id'."
            } else {
                $seenIds[$id] = $true
            }

            Test-SourceDocPath -RelativePath (Join-Path $docRoot $doc) -Context "$($indexFile.Name) row '$id'"
        }
    }

    if ($totalRows -ne $ExpectedSourceCount) {
        Add-Failure "Category index row count is $totalRows, expected $ExpectedSourceCount."
    }

    return $totalRows
}

function Test-SourceDocs {
    $sourceFiles = Get-ChildItem -Path $SourceRoot -Recurse -Filter "*.md" | Sort-Object FullName

    if ($sourceFiles.Count -ne $ExpectedSourceCount) {
        Add-Failure "Source doc count is $($sourceFiles.Count), expected $ExpectedSourceCount."
    }

    foreach ($file in $sourceFiles) {
        $text = Get-MarkdownText -Path $file.FullName
        $decisionCount = ([regex]::Matches($text, "(?m)^## Decision Summary\s*$")).Count
        if ($decisionCount -ne 1) {
            Add-Failure "$($file.FullName) has $decisionCount Decision Summary sections."
        }

        if ($text -match "(?m)^---[ \t]+title:") {
            Add-Failure "$($file.FullName) appears to contain collapsed frontmatter/source text."
        }

        if ($text -match '\$symbol|\$usage|\x07') {
            Add-Failure "$($file.FullName) contains generated placeholder/control tokens."
        }

        if ($text -match "(?m)^- \*\*(Use when|Do not use when|Requires|Conflicts|Prefer instead):\*\*\s*$") {
            Add-Failure "$($file.FullName) contains an empty Decision Summary bullet."
        }
    }

    return $sourceFiles.Count
}

function Test-InternalMarkdownLinks {
    $missing = 0
    $linkPattern = [regex]"\[[^\]]+\]\((?!https?://|mailto:|#)([^)#]+\.md)(?:#[^)]+)?\)"

    foreach ($file in Get-ChildItem -Path $SourceRoot -Recurse -Filter "*.md") {
        $text = Get-MarkdownText -Path $file.FullName
        foreach ($match in $linkPattern.Matches($text)) {
            $target = $match.Groups[1].Value
            $resolved = Join-Path $file.DirectoryName $target
            if (-not (Test-Path -Path $resolved -PathType Leaf)) {
                Add-Failure "$($file.FullName) links to missing markdown file: $target"
                $missing += 1
            }
        }
    }

    return $missing
}

function Test-AmbiguousCoverage {
    $duplicateNames = Get-ChildItem -Path $SourceRoot -Recurse -Filter "*.md" |
        Group-Object { [System.IO.Path]::GetFileNameWithoutExtension($_.Name) } |
        Where-Object { $_.Count -gt 1 } |
        ForEach-Object { $_.Name }

    $ambiguousRows = Get-TableRows -Path (Join-Path $IndexRoot "ambiguous-symbols.index.md")
    $ambiguousNames = $ambiguousRows |
        ForEach-Object { Unwrap-CodeCell (Get-Cell -Row $_ -Index 1) } |
        Sort-Object -Unique

    $missing = @($duplicateNames | Where-Object { $_ -notin $ambiguousNames })
    foreach ($name in $missing) {
        Add-Failure "Duplicate source symbol '$name' is missing from ambiguous-symbols.index.md."
    }

    return @{
        DuplicateSymbolCount = $duplicateNames.Count
        MissingCoverageCount = $missing.Count
    }
}

function Test-SourcesIndexFiles {
    $sourcesIndex = Join-Path $IndexRoot "sources.index.md"
    foreach ($row in Get-TableRows -Path $sourcesIndex) {
        $category = Get-Cell -Row $row -Index 1
        $fileName = Unwrap-CodeCell (Get-Cell -Row $row -Index 2)
        $resolved = Join-Path $CategoryIndexRoot $fileName
        if (-not (Test-Path -Path $resolved -PathType Leaf)) {
            Add-Failure "sources.index.md row '$category' points to missing index file: $fileName"
        }
    }
}

function Test-StaleTokens {
    $docZhRoot = Join-Path $RepoRoot "Doc\zh"
    $roots = @($SkillRoot)
    if (Test-Path -Path $docZhRoot -PathType Container) {
        $roots += $docZhRoot
    }

    $tokens = @("DetaisPanel", "source_doc", "Signals", "empty Doc")
    $matches = New-Object System.Collections.Generic.List[string]

    foreach ($root in $roots) {
        foreach ($file in Get-ChildItem -Path $root -Recurse -File) {
            if ($file.FullName -eq $ThisScript) {
                continue
            }
            if ($file.Extension -notin @(".md", ".ps1")) {
                continue
            }

            $text = Get-MarkdownText -Path $file.FullName
            foreach ($token in $tokens) {
                if ($text.Contains($token)) {
                    $matches.Add("$($file.FullName): $token") | Out-Null
                }
            }
        }
    }

    foreach ($match in $matches) {
        Add-Failure "Stale token found: $match"
    }

    return $matches.Count
}

$sourceCount = Test-SourceDocs
$categoryRows = Test-CategoryIndexDocTables
$commonRows = Test-IndexDocTable -Path (Join-Path $IndexRoot "common.index.md") -ExpectedRows $ExpectedCommonRows -Label "common.index.md"
$constraintRows = Test-IndexDocTable -Path (Join-Path $IndexRoot "constraints.index.md") -ExpectedRows $ExpectedConstraintRows -Label "constraints.index.md"
$ambiguousRows = Test-IndexDocTable -Path (Join-Path $IndexRoot "ambiguous-symbols.index.md") -ExpectedRows $ExpectedAmbiguousRows -Label "ambiguous-symbols.index.md"
Test-SourcesIndexFiles
$missingLinks = Test-InternalMarkdownLinks
$staleTokenMatches = Test-StaleTokens
$ambiguousCoverage = Test-AmbiguousCoverage

if ($Failures.Count -gt 0) {
    Write-Host "ue-specifiers validation failed:" -ForegroundColor Red
    foreach ($failure in $Failures) {
        Write-Host "  - $failure"
    }
    exit 1
}

Write-Host "ue-specifiers validation passed." -ForegroundColor Green
Write-Host "  source docs: $sourceCount"
Write-Host "  category index rows: $categoryRows"
Write-Host "  common rows: $commonRows"
Write-Host "  constraint rows: $constraintRows"
Write-Host "  ambiguous rows: $ambiguousRows"
Write-Host "  duplicate source symbol groups: $($ambiguousCoverage.DuplicateSymbolCount)"
Write-Host "  missing ambiguous coverage: $($ambiguousCoverage.MissingCoverageCount)"
Write-Host "  missing internal markdown links: $missingLinks"
Write-Host "  stale token matches: $staleTokenMatches"
