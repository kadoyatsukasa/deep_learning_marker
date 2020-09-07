#include "CVGraphicsModel.h"

CVGraphicsModel::CVGraphicsModel()
{
}

CVGraphicsModel* CVGraphicsModel::instance()
{
	static CVGraphicsModel ins;
	return &ins;
}