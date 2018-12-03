void Net_SaveFile(bool bServer, ref rObject, string sFileName){}
void Net_LoadFile(bool bServer, ref rObject, string sFileName){}
int Net_GetTickCount(){return 0;}
void Net_Sort2i(ref rInMassive, ref rOutMassive, int iDirection, int iMaxOutNum, string sAttribute1, string sAttribute2){}
int NetIni_GetLong(string sIniFile, string sSection, string sValue){return 0;}
string NetIni_GetString(string sIniFile, string sSection, string sValue){return "";}
void NetServer_AddClient(int wClientID, int dwIP, int wPort){}
void NetServer_DelClient(int wClientID){}
void NetServer_SendMessage(int wClientID, int iMsg, bool bGarantedDelivery){}
void NetServer_SendMessageAllExcept(int wClientID, int iMsg, bool bGarantedDelivery){}
void NetServer_SendMessageDirect(int dwIP, int wPort, int iMsg){}
void NetServer_SendMasterServerMessage(string sAddress, int wPort, int iMsg){}
void NetServer_GarantedDeliveryCallback(int wClientID, int byGarantedDeliveryIndex){}
void NetServer_ClearPacketsQueue(){}
void NetClient_SendMessage(int iMsg, bool bGarantedDelivery){}
void NetClient_SendMessageDirect(int iMsg){}
void NetClient_SendMessageDirectToIP(int dwIP, int wPort, int iMsg){}
void NetClient_SendBroadcastMessage(int iMsg){}
void NetClient_SendMasterServerMessage(string sAddress, int wPort, int iMsg){}
void NetClient_GarantedDeliveryCallback(int byGarantedDeliveryIndex){}
void NetClient_ClearPacketsQueue(){}
void NMAddByte(int iSMsg, int bByte){}
void NMAddWord(int iSMsg, int wWord){}
void NMAddDword(int iSMsg, int dDword){}
void NMAdd24(int iSMsg, int dDword){}
void NMAddFloat(int iSMsg, float fFloat){}
void NMAddString(int iSMsg, string sString, int iMaxLen){}
void NMAddData(int iSMsg, int pData, int iSize){}
int NMCreate(){return 0;}
void NMDelete(int iMsg){}
int NMNotEmpty(int iMsg){return 0;}
int NMGetByte(int iMsg){return 0;}
int NMGetWord(int iMsg){return 0;}
int NMGetDword(int iMsg){return 0;}
int NMGet24(int iMsg){return 0;}
float NMGetFloat(int iMsg){return 0;}
string NMGetString(int iMsg){return "";}
string inet_ntoa(int dwIP){return "";}
string inet_ntoax(int dwIP){return "";}
int ntohs(int wPort){return 0;}
int NFFindFiles(ref rObject, string sDirectory, string sMask, bool bRecursive){return 0;}
int NFExist(string sFileName){return 0;}
int NFRCreateFile(int wClientID, string sFileName, int iEventID, int iEventSubID){return 0;}
void NFRReceiveData(int iFileID, int iIndex, int iMsg){}
void NFRDeleteFile(int iFileID){}
int NFRIsEqualFile(int iFileID, int iCRC32, int iSize){return 0;}
void NFRSetSendHandle(int iFileID1, int iFileID2, int iFileSize){}
int NFSCreateFile(int wClientID, int iRecvHandler, string sFileName){return 0;}
void NFSDeleteFile(int iFileID){}
void NFSReceiverReady(int iFileID){}
void NFSDataACK(int iFileID, int iIndex){}
int NFGetTexture(string sGroupID, string sFilename){return 0;}
void NFDelTexture(string sGroupID, string sFilename){}
void NFDelGroupTextures(string sGroupID){}