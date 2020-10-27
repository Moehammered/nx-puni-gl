#include "glmhelpers.h"

std::string Vec3ToString(glm::vec3 const& v3)
{
    std::string st;

    st.append("(");
    st.append(std::to_string(v3.x));
    st.append(", ");
    st.append(std::to_string(v3.y));
    st.append(",");
    st.append(std::to_string(v3.z));
    st.append(")");

    return st;
}
