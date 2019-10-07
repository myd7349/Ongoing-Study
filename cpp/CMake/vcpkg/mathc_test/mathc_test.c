#include <mathc.h>

int main(void)
{
    mfloat_t position[VEC3_SIZE];
    mfloat_t scaling[VEC3_SIZE];
    struct {
        mfloat_t position[MAT4_SIZE];
        mfloat_t rotation[MAT4_SIZE];
        mfloat_t scaling[MAT4_SIZE];
        mfloat_t model[MAT4_SIZE];
    } matrices;

    /* Position */
    mat4_identity(matrices.position);
    //mat4_translation(matrices.position, vec3(position, 0.0, 0.0, 0.0));

    /* Rotation */
    mat4_identity(matrices.rotation);
    mat4_rotation_x(matrices.rotation, to_radians(30.0));

    /* Scaling */
    mat4_identity(matrices.scaling);
    //mat4_translation(matrices.scaling, vec3(scaling, 1.0, 1.0, 1.0));

    /* Model matrix */
    mat4_multiply(matrices.model, matrices.scaling, matrices.rotation);
    mat4_multiply(matrices.model, matrices.position, matrices.model);

    return 0;
}
