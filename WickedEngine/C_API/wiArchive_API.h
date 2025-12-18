#pragma once
#include "wiC_API.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct wiArchive_t *wiArchive;

// Lifecycle
wiArchive wiArchive_Create(void);
wiArchive wiArchive_CreateFromFile(const char *fileName, bool readMode);
wiArchive wiArchive_CreateFromMemory(const uint8_t *data, size_t size);
void wiArchive_Destroy(wiArchive archive);

// Management
bool wiArchive_IsOpen(wiArchive archive);
bool wiArchive_IsReadMode(wiArchive archive);
void wiArchive_SetReadModeAndResetPos(wiArchive archive, bool isReadMode);
void wiArchive_Close(wiArchive archive);
bool wiArchive_SaveFile(wiArchive archive, const char *fileName);
const char *wiArchive_GetSourceDirectory(wiArchive archive);
const char *wiArchive_GetSourceFileName(wiArchive archive);
size_t wiArchive_GetPos(wiArchive archive);
size_t wiArchive_GetSize(wiArchive archive);

// Write Operations
void wiArchive_WriteBool(wiArchive archive, bool value);
void wiArchive_WriteInt(wiArchive archive, int value);
void wiArchive_WriteUInt(wiArchive archive, unsigned int value);
void wiArchive_WriteLong(wiArchive archive, long long value);
void wiArchive_WriteULong(wiArchive archive, unsigned long long value);
void wiArchive_WriteFloat(wiArchive archive, float value);
void wiArchive_WriteDouble(wiArchive archive, double value);
void wiArchive_WriteVector(wiArchive archive, wiVector value); // Writes x,y,z,w
void wiArchive_WriteVector2(wiArchive archive, wiVector value); // Writes x,y
void wiArchive_WriteVector3(wiArchive archive, wiVector value); // Writes x,y,z
void wiArchive_WriteColor(wiArchive archive, wiColor value);
void wiArchive_WriteString(wiArchive archive, const char *value);

// Read Operations
bool wiArchive_ReadBool(wiArchive archive);
int wiArchive_ReadInt(wiArchive archive);
unsigned int wiArchive_ReadUInt(wiArchive archive);
long long wiArchive_ReadLong(wiArchive archive);
unsigned long long wiArchive_ReadULong(wiArchive archive);
float wiArchive_ReadFloat(wiArchive archive);
double wiArchive_ReadDouble(wiArchive archive);
wiVector wiArchive_ReadVector(wiArchive archive);
wiVector wiArchive_ReadVector2(wiArchive archive);
wiVector wiArchive_ReadVector3(wiArchive archive);
wiColor wiArchive_ReadColor(wiArchive archive);
const char *
wiArchive_ReadString(wiArchive archive); // Returns internal thread_local buffer

#ifdef __cplusplus
}
#endif
