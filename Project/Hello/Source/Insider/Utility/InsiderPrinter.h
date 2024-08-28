#pragma once

#include "InsiderTypes.h"




class FInsiderPrinter :public TStringBuilder<102400>
{
public:
	FString Prefix;

public:
	FInsiderPrinter(const FString& prefix) :Prefix(prefix) {}

public:
	void PrintStructHeader(const FString& name);
	void PrintBeginArray(const FString& name, int32 size);
	void PrintEndArray();
	void PrintBeginArrayItem(int32 index);
	void PrintEndArrayItem();



	template<typename T>
	void PrintNamedValue(const FString& name, const T& value, bool addNewLine = true)
	{
		*this << Prefix;
		*this << name;
		*this << FString(TEXT(":\t"));
		*this << value;
		if (addNewLine)
		{
			AppendChar('\n');
		}
	}


public:
	void AddIndent(int steps = 1);
	void RemoveIndent(int steps = 1);
protected:

};

struct FInsiderPrinterScope
{
	FInsiderPrinterScope(FInsiderPrinter& printer)
		:Printer(printer)
	{
		Printer.AddIndent();
	}
	~FInsiderPrinterScope()
	{
		Printer.RemoveIndent();
	}
	FInsiderPrinter& Printer;
};

struct FInsiderPrinter_EnterArray
{
	FInsiderPrinter_EnterArray(FInsiderPrinter& printer, const FString& name, int32 size)
		:Printer(printer)
	{
		Printer.PrintBeginArray(name, size);
	}
	~FInsiderPrinter_EnterArray()
	{
		Printer.PrintEndArray();
	}
	FInsiderPrinter& Printer;
};

struct FInsiderPrinter_EnterArray_Item
{
	FInsiderPrinter_EnterArray_Item(FInsiderPrinter& printer, int32 index)
		:Printer(printer)
	{
		Printer.AddIndent();
		Printer.PrintBeginArrayItem(index);
		Printer.AddIndent();

	}
	~FInsiderPrinter_EnterArray_Item()
	{
		Printer.RemoveIndent();
		Printer.PrintEndArrayItem();
		Printer.RemoveIndent();

	}
	FInsiderPrinter& Printer;
};

#define PRINT_STRUCT_PROPERTY(printer,Object,Property) printer.PrintNamedValue(TEXT(#Property),Object.Property);
