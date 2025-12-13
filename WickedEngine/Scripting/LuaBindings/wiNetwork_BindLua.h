#pragma once
#include "Scripting/wiLua.h"
#include "Scripting/wiLuna.h"

namespace wi::lua {

class Network_BindLua {
public:
  inline static constexpr char className[] = "Network";
  static Luna<Network_BindLua>::FunctionType methods[];
  static Luna<Network_BindLua>::PropertyType properties[];

  Network_BindLua() = default;
  Network_BindLua(lua_State *L) {}

  static void Bind();
};

} // namespace wi::lua
