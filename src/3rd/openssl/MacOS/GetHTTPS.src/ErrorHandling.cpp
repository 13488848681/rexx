
 #include "ErrorHandling.hpp"
#include "CPStringUtils.hpp"

#ifdef __EXCEPTIONS_ENABLED__
	#include "CMyException.hpp"
#endif


static char					gErrorMessageBuffer[512];

char 						*gErrorMessage = gErrorMessageBuffer;
int							gErrorMessageMaxLength = sizeof(gErrorMessageBuffer);



void SetErrorMessage(const char *theErrorMessage)
{
	if (theErrorMessage != nil)
	{
		CopyCStrToCStr(theErrorMessage,gErrorMessage,gErrorMessageMaxLength);
	}
}


void SetErrorMessageAndAppendLongInt(const char *theErrorMessage,const long theLongInt)
{
	if (theErrorMessage != nil)
	{
		CopyCStrAndConcatLongIntToCStr(theErrorMessage,theLongInt,gErrorMessage,gErrorMessageMaxLength);
	}
}

void SetErrorMessageAndCStrAndLongInt(const char *theErrorMessage,const char * theCStr,const long theLongInt)
{
	if (theErrorMessage != nil)
	{
		CopyCStrAndInsertCStrLongIntIntoCStr(theErrorMessage,theCStr,theLongInt,gErrorMessage,gErrorMessageMaxLength);
	}

}

void SetErrorMessageAndCStr(const char *theErrorMessage,const char * theCStr)
{
	if (theErrorMessage != nil)
	{
		CopyCStrAndInsertCStrLongIntIntoCStr(theErrorMessage,theCStr,-1,gErrorMessage,gErrorMessageMaxLength);
	}
}


void AppendCStrToErrorMessage(const char *theErrorMessage)
{
	if (theErrorMessage != nil)
	{
		ConcatCStrToCStr(theErrorMessage,gErrorMessage,gErrorMessageMaxLength);
	}
}


void AppendLongIntToErrorMessage(const long theLongInt)
{
	ConcatLongIntToCStr(theLongInt,gErrorMessage,gErrorMessageMaxLength);
}



char *GetErrorMessage(void)
{
	return gErrorMessage;
}


OSErr GetErrorMessageInNewHandle(Handle *inoutHandle)
{
OSErr		errCode;


	errCode = CopyCStrToNewHandle(gErrorMessage,inoutHandle);
	
	return(errCode);
}


OSErr GetErrorMessageInExistingHandle(Handle inoutHandle)
{
OSErr		errCode;


	errCode = CopyCStrToExistingHandle(gErrorMessage,inoutHandle);
	
	return(errCode);
}



OSErr AppendErrorMessageToHandle(Handle inoutHandle)
{
OSErr		errCode;


	errCode = AppendCStrToHandle(gErrorMessage,inoutHandle,nil);
	
	return(errCode);
}


#ifdef __EXCEPTIONS_ENABLED__

void ThrowErrorMessageException(void)
{
	ThrowDescriptiveException(gErrorMessage);
}

#endif
