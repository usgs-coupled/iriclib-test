#include "error_macros.h"
#include "iriclib_errorcodes.h"
#include "iriclib.h"
#include "h5cgnsbase.h"
#include "h5cgnsbaseiterativedata.h"
#include "h5cgnsfile.h"

#include "internal/iric_h5cgnsfiles.h"
#include "internal/iric_logger.h"
#include "internal/iric_outputerror.h"

#include <Poco/File.h>

#include <algorithm>
#include <sstream>

using namespace iRICLib;

#define GET_F \
	H5CgnsFile* file = nullptr;\
	int ier = _iric_h5cgnsfiles_get(fid, &file);\
	RETURN_IF_ERR;

int cg_iRIC_Read_Sol_Count(int fid, int* count)
{
	_IRIC_LOGGER_TRACE_ENTER();

	GET_F;

	std::vector<double> times;
	std::vector<int> iterations;
	ier = file->ccBase()->biterData()->readTime(&times);
	RETURN_IF_ERR;
	ier = file->ccBase()->biterData()->readIteration(&iterations);
	RETURN_IF_ERR;

	auto tmpCount = times.size();
	if (tmpCount < iterations.size()) {tmpCount = iterations.size();}

	*count = static_cast<int> (tmpCount);

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Sol_Time(int fid, int step, double* time)
{
	_IRIC_LOGGER_TRACE_ENTER();

	GET_F;

	ier = file->ccBase()->biterData()->readTime(step, time);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Sol_Iteration(int fid, int step, int* index)
{
	_IRIC_LOGGER_TRACE_ENTER();

	GET_F;

	ier = file->ccBase()->biterData()->readIteration(step, index);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Sol_BaseIterative_Integer(int fid, int step, const char* name, int* value)
{
	_IRIC_LOGGER_TRACE_ENTER();

	GET_F;

	ier = file->ccBase()->biterData()->readValue(step, name, value);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Sol_BaseIterative_Real(int fid, int step, const char* name, double* value)
{
	_IRIC_LOGGER_TRACE_ENTER();

	GET_F;

	ier = file->ccBase()->biterData()->readValue(step, name, value);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Sol_BaseIterative_StringLen(int fid, int step, const char* name, int* length)
{
	_IRIC_LOGGER_TRACE_ENTER();

	GET_F;

	std::string value;
	ier = file->ccBase()->biterData()->readValue(step, name, &value);
	RETURN_IF_ERR;

	*length = static_cast<int> (value.length());

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Sol_BaseIterative_String(int fid, int step, const char* name, char* strvalue)
{
	_IRIC_LOGGER_TRACE_ENTER();

	GET_F;

	std::string value;
	ier = file->ccBase()->biterData()->readValue(step, name, &value);
	RETURN_IF_ERR;

	for (size_t i = 0; i < value.length(); ++i) {
		*(strvalue + i) = *(value.data() + i);
	}
	*(strvalue + value.length()) = '\0';

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_Sol_Start(int fid)
{
	_IRIC_LOGGER_TRACE_ENTER();

	H5CgnsFile* file;
	int ier = _iric_h5cgnsfiles_get(fid, &file);
	RETURN_IF_ERR;

	ier = file->solutionWriter()->writeSolStart();
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_Sol_End(int fid)
{
	_IRIC_LOGGER_TRACE_ENTER();

	Poco::File f(".flush");
	if (! f.exists()) {
		return IRIC_NO_ERROR;
	}

	H5CgnsFile* file;
	int ier = _iric_h5cgnsfiles_get(fid, &file);
	RETURN_IF_ERR;

	ier = file->solutionWriter()->flush();
	RETURN_IF_ERR;

	f.remove();

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_Sol_Time(int fid, double time)
{
	_IRIC_LOGGER_TRACE_ENTER();

	GET_F;

	ier = file->solutionWriter()->writeTime(time);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_Sol_Iteration(int fid, int index)
{
	_IRIC_LOGGER_TRACE_ENTER();

	GET_F;

	ier = file->solutionWriter()->writeIteration(index);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_Sol_BaseIterative_Integer(int fid, const char* name, int value)
{
	_IRIC_LOGGER_TRACE_ENTER();

	GET_F;

	ier = file->solutionWriter()->writeBaseIterativeData(name, value);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_Sol_BaseIterative_Real(int fid, const char* name, double value)
{
	_IRIC_LOGGER_TRACE_ENTER();

	GET_F;

	ier = file->solutionWriter()->writeBaseIterativeData(name, value);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_Sol_BaseIterative_String(int fid, const char* name, const char* value)
{
	_IRIC_LOGGER_TRACE_ENTER();

	GET_F;

	ier = file->solutionWriter()->writeBaseIterativeData(name, value);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_ErrorCode(int fid, int errorcode)
{
	_IRIC_LOGGER_TRACE_ENTER();

	GET_F;

	ier = file->ccBase()->writeErrorCode(errorcode);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}
