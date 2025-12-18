#include "wiArchive_API.h"
#include "../wiArchive.h"
#include "../wiMath.h"

using namespace wi;

static thread_local std::string _tempString;

extern "C" {

wiArchive wiArchive_Create(void) { return (wiArchive) new Archive(); }

wiArchive wiArchive_CreateFromFile(const char *fileName, bool readMode) {
  return (wiArchive) new Archive(fileName, readMode);
}

wiArchive wiArchive_CreateFromMemory(const uint8_t *data, size_t size) {
  return (wiArchive) new Archive(data, size);
}

void wiArchive_Destroy(wiArchive archive) {
  if (archive) {
    delete ((Archive *)archive);
  }
}

bool wiArchive_IsOpen(wiArchive archive) {
  if (archive)
    return ((Archive *)archive)->IsOpen();
  return false;
}

bool wiArchive_IsReadMode(wiArchive archive) {
  if (archive)
    return ((Archive *)archive)->IsReadMode();
  return false;
}

void wiArchive_SetReadModeAndResetPos(wiArchive archive, bool isReadMode) {
  if (archive)
    ((Archive *)archive)->SetReadModeAndResetPos(isReadMode);
}

void wiArchive_Close(wiArchive archive) {
  if (archive)
    ((Archive *)archive)->Close();
}

bool wiArchive_SaveFile(wiArchive archive, const char *fileName) {
  if (archive)
    return ((Archive *)archive)->SaveFile(fileName);
  return false;
}

const char *wiArchive_GetSourceDirectory(wiArchive archive) {
  if (archive)
    return ((Archive *)archive)->GetSourceDirectory().c_str();
  return "";
}

const char *wiArchive_GetSourceFileName(wiArchive archive) {
  if (archive)
    return ((Archive *)archive)->GetSourceFileName().c_str();
  return "";
}

size_t wiArchive_GetPos(wiArchive archive) {
  if (archive)
    return ((Archive *)archive)->GetPos();
  return 0;
}

size_t wiArchive_GetSize(wiArchive archive) {
  if (archive)
    return ((Archive *)archive)->GetSize();
  return 0;
}

// Write
void wiArchive_WriteBool(wiArchive archive, bool value) {
  if (archive)
    (*((Archive *)archive)) << value;
}
void wiArchive_WriteInt(wiArchive archive, int value) {
  if (archive)
    (*((Archive *)archive)) << value;
}
void wiArchive_WriteUInt(wiArchive archive, unsigned int value) {
  if (archive)
    (*((Archive *)archive)) << value;
}
void wiArchive_WriteLong(wiArchive archive, long long value) {
  if (archive)
    (*((Archive *)archive)) << value;
}
void wiArchive_WriteULong(wiArchive archive, unsigned long long value) {
  if (archive)
    (*((Archive *)archive)) << value;
}
void wiArchive_WriteFloat(wiArchive archive, float value) {
  if (archive)
    (*((Archive *)archive)) << value;
}
void wiArchive_WriteDouble(wiArchive archive, double value) {
  if (archive)
    (*((Archive *)archive)) << value;
}
void wiArchive_WriteVector(wiArchive archive, wiVector value) {
  if (archive)
    (*((Archive *)archive)) << XMFLOAT4(value.x, value.y, value.z, value.w);
}
void wiArchive_WriteVector2(wiArchive archive, wiVector value) {
  if (archive)
    (*((Archive *)archive)) << XMFLOAT2(value.x, value.y);
}
void wiArchive_WriteVector3(wiArchive archive, wiVector value) {
  if (archive)
    (*((Archive *)archive)) << XMFLOAT3(value.x, value.y, value.z);
}
void wiArchive_WriteColor(wiArchive archive, wiColor value) {
  if (archive) {
    wi::Color c;
    c.setR(value.r);
    c.setG(value.g);
    c.setB(value.b);
    c.setA(value.a);
    (*((Archive *)archive)) << c;
  }
}
void wiArchive_WriteString(wiArchive archive, const char *value) {
  if (archive)
    (*((Archive *)archive)) << std::string(value ? value : "");
}

// Read
bool wiArchive_ReadBool(wiArchive archive) {
  bool val = false;
  if (archive)
    (*((Archive *)archive)) >> val;
  return val;
}
int wiArchive_ReadInt(wiArchive archive) {
  int val = 0;
  if (archive)
    (*((Archive *)archive)) >> val;
  return val;
}
unsigned int wiArchive_ReadUInt(wiArchive archive) {
  unsigned int val = 0;
  if (archive)
    (*((Archive *)archive)) >> val;
  return val;
}
long long wiArchive_ReadLong(wiArchive archive) {
  long long val = 0;
  if (archive)
    (*((Archive *)archive)) >> val;
  return val;
}
unsigned long long wiArchive_ReadULong(wiArchive archive) {
  unsigned long long val = 0;
  if (archive)
    (*((Archive *)archive)) >> val;
  return val;
}
float wiArchive_ReadFloat(wiArchive archive) {
  float val = 0;
  if (archive)
    (*((Archive *)archive)) >> val;
  return val;
}
double wiArchive_ReadDouble(wiArchive archive) {
  double val = 0;
  if (archive)
    (*((Archive *)archive)) >> val;
  return val;
}
wiVector wiArchive_ReadVector(wiArchive archive) {
  wiVector val = {0};
  if (archive) {
    XMFLOAT4 v;
    (*((Archive *)archive)) >> v;
    val.x = v.x;
    val.y = v.y;
    val.z = v.z;
    val.w = v.w;
  }
  return val;
}
wiVector wiArchive_ReadVector2(wiArchive archive) {
  wiVector val = {0};
  if (archive) {
    XMFLOAT2 v;
    (*((Archive *)archive)) >> v;
    val.x = v.x;
    val.y = v.y;
  }
  return val;
}
wiVector wiArchive_ReadVector3(wiArchive archive) {
  wiVector val = {0};
  if (archive) {
    XMFLOAT3 v;
    (*((Archive *)archive)) >> v;
    val.x = v.x;
    val.y = v.y;
    val.z = v.z;
  }
  return val;
}
wiColor wiArchive_ReadColor(wiArchive archive) {
  wiColor val = {0};
  if (archive) {
    wi::Color c;
    (*((Archive *)archive)) >> c;
    val.r = c.getR();
    val.g = c.getG();
    val.b = c.getB();
    val.a = c.getA();
  }
  return val;
}
const char *wiArchive_ReadString(wiArchive archive) {
  if (archive) {
    (*((Archive *)archive)) >> _tempString;
    return _tempString.c_str();
  }
  return "";
}
}
