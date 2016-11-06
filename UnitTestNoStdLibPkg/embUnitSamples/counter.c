//#include <stdlib.h> //uncomment when trying to build a version using the UEFI StdLib package
#include "counter.h"
//The below includes have calls that provide similar functionality so the stdlib calls
//this file was written to depend on.
#include <Library/UefiBootServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>

CounterRef Counter_alloc(void)
{
	return (CounterRef)AllocatePool(sizeof(Counter));
}

void Counter_dealloc(CounterRef self)
{
	gBS->FreePool(self);
}

CounterRef Counter_init(CounterRef self)
{
	self->value = 0;
	return self;
}

CounterRef Counter_counter(void)
{
	return Counter_init(Counter_alloc());
}

int Counter_value(CounterRef self)
{
	return self->value;
}

void Counter_setValue(CounterRef self,int value)
{
	self->value = value;
}

int Counter_inc(CounterRef self)
{
	self->value++;
	return self->value;
}

int Counter_dec(CounterRef self)
{
	self->value--;
	return self->value;
}

void Counter_clr(CounterRef self)
{
	self->value = 0;
}
