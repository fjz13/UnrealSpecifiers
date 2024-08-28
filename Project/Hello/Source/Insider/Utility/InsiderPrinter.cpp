#include "InsiderPrinter.h"


void FInsiderPrinter::PrintStructHeader(const FString& name)
{
	PrintNamedValue(name, FString(), true);
}

void FInsiderPrinter::PrintBeginArray(const FString& name, int32 size)
{
	*this<< Prefix;
	*this<< name;
	AppendChar('[');
	*this<<size;
	Append("]:\n");

	*this<< Prefix;
	Append("[\n");

}

void FInsiderPrinter::PrintEndArray()
{
	*this<< Prefix;
	Append("]\n");
}

void FInsiderPrinter::PrintBeginArrayItem(int32 index)
{
	*this<< Prefix;
	Append("{\t//[");
	*this<<index;
	Append("]\n");

}
void FInsiderPrinter::PrintEndArrayItem()
{
	*this<< Prefix;
	Append("},\n");
}

void FInsiderPrinter::AddIndent(int steps/*=1*/)
{
	for (int i = 0; i < steps; ++i)
	{
		Prefix.AppendChar('\t');
	}
}

void FInsiderPrinter::RemoveIndent(int steps/*=1*/)
{
	Prefix.RemoveAt(Prefix.Len() - steps, steps);
}
