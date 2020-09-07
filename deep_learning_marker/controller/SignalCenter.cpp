#include "SignalCenter.h"

SignalCenter::SignalCenter()
{
}

SignalCenter* SignalCenter::instance()
{
	static SignalCenter ins;
	return &ins;
}