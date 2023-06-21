#pragma once
#include "definitions.h"



extern "C" POBJECT_TYPE * IoDriverObjectType;

typedef VOID
(*MouseClassServiceCallback)(
	PDEVICE_OBJECT DeviceObject,
	PMOUSE_INPUT_DATA InputDataStart,
	PMOUSE_INPUT_DATA InputDataEnd,
	PULONG InputDataConsumed
	);



namespace mouse
{
	NTSTATUS init_mouse(PMOUSE_OBJECT mouse_obj);

	void mouse_event(MOUSE_OBJECT mouse_obj, long x, long y, unsigned short flags);
}