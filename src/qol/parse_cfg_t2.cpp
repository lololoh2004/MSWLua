#include "mswlua/qol/parse_cfg_t2.hpp"
#include "mswlua/luaState/state.hpp"


cfgParserFFI::cfgParserFFI(luaState& state){
    m_state = state.getRawState();
}
