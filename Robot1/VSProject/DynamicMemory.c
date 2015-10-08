#include <stdlib.h>
#include <task.h>
#include <portable.h>

void *operator new(size_t size)
{
	void *p;

	if (uxTaskGetNumberOfTasks())
		p = pvPortMalloc(size);
	else
		p = malloc(size);

	return p;
}

void operator delete(void *p)
{
	if (uxTaskGetNumberOfTasks())
		vPortFree(p);
	else
		free(p);

	p = NULL;
}