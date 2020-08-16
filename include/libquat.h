/**
  @file libquat.h
  @brief
  @version @LIBQUAT_VERSION_MAJOR@.@LIBQUAT_VERSION_MINOR@
  @author Krishna Vedala
  @copyright
*/

#ifndef __LIBQUAT_H_
#define __LIBQUAT_H_

#define LIBQUAT_EPSILON                                               \
    1e-9 /**< Minimum recognizable value. Any value less than this is \
            considered to be @f$=0@f$ */

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @addtogroup errors Error module
     * @{
     */
    /** Library return types indicating different error types. */
    typedef enum
    {
        LIBQUAT_OK = 0,      /**< No error */
        LIBQUAT_BAD_VERSION, /**< header and library version do not match */
        LIBQUAT_DIV_BY_ZERO, /**< Division by zero */
    } libquat_err;

    /**
     * Obtain descriptive string message for a #libquat_err type error code.
     * @param[in] err_code error code from the library api calls
     * @return error description string
     */
    const char *err_to_str(libquat_err err_code);

    /**
     * Function to check the version number of the library with the header.
     * @param[in] major_ver provide major version as input
     * @return error of type #libquat_err
     */
    libquat_err libquat_version_check(const char major_ver);
    /** @} */

    /**
     * @addtogroup matrix Matrix operations
     * @{
     */
    /** A 3x3 Matrix typedfinition */
    typedef struct mat_3x3_
    {
        float row1[3]; /**< 3 element row 1 */
        float row2[3]; /**< 3 element row 2 */
        float row3[3]; /**< 3 element row 3 */
    } mat_3x3;
    /** @} */

    /**
     * @addtogroup vec_3d 3D Vector operations
     * @{
     */
    /** 3D vector type */
    typedef struct vec_3d_
    {
        float x; /**< X co-ordinate */
        float y; /**< Y co-ordinate */
        float z; /**< Z co-ordinate */
    } vec_3d;

    /**
     * Obtain the dot product of two 3D vectors.
     * @f[
     * \vec{a}\cdot\vec{b}=a_xb_x + a_yb_y + a_zb_z
     * @f]
     * @param[in] a first vector
     * @param[in] b second vector
     * @param[out] o resulting dot product
     */
    void dot_prod(const vec_3d *a, const vec_3d *b, float *o);

    /**
     * Subtract one vector from another. @f[
     * \vec{c}=\vec{a}-\vec{b}=\left(a_x-b_x\right)\hat{i}+
     * \left(a_y-b_y\right)\hat{j}+\left(a_z-b_z\right)\hat{k}@f]
     * @param[in] a vector to subtract from
     * @param[in] b vector to subtract
     * @param[out] out resultant vector
     */
    void vector_sub(const vec_3d *a, const vec_3d *b, vec_3d *out);

    /**
     * Add one vector to another. @f[
     * \vec{c}=\vec{a}+\vec{b}=\left(a_x+b_x\right)\hat{i}+
     * \left(a_y+b_y\right)\hat{j}+\left(a_z+b_z\right)\hat{k}@f]
     * @param[in] a vector to add to
     * @param[in] b vector to add
     * @param[out] out resultant vector
     */
    void vector_add(const vec_3d *a, const vec_3d *b, vec_3d *out);

    /**
     * Compute the vector product of two 3d vectors.
     * @f[\begin{align*}
     * \vec{a}\times\vec{b} &= \begin{vmatrix}
     *  \hat{i} & \hat{j} & \hat{k}\\
     *  a_x & a_y & a_z\\
     *  b_x & b_y & b_z
     *  \end{vmatrix}\\
     *  &= \left(a_yb_z-b_ya_z\right)\hat{i} - \left(a_xb_z-b_xa_z\right)\hat{j}
     * + \left(a_xb_y-b_xa_y\right)\hat{k} \end{align*}
     * @f]
     * @param[in] a first vector @f$\vec{a}@f$
     * @param[in] b second vector @f$\vec{b}@f$
     * @param[out] o resultant vector @f$\vec{o}=\vec{a}\times\vec{b}@f$
     */
    void vector_prod(const vec_3d *a, const vec_3d *b, vec_3d *o);

    /**
     * Print formatted vector on stdout.
     * @param[in] a vector to print
     * @param[in] name  name of the vector
     */
    const char *print_vector(const vec_3d *a, const char *name);

    /**
     * Compute the norm a vector.
     * @f[\lVert\vec{a}\rVert = \sqrt{\vec{a}\cdot\vec{a}} @f]
     * @param[in] a input vector
     * @param[out] n norm of the given vector
     */
    void vector_norm(const vec_3d *a, float *n);

    /**
     * Obtain unit vector in the same direction as given vector.
     * @f[\hat{a}=\frac{\vec{a}}{\lVert\vec{a}\rVert}@f]
     * @param[in] a input vector
     * @param[out] a_hat unit vector in the direction of @f$\vec{a}@f$
     */
    libquat_err unit_vec(const vec_3d *a, vec_3d *a_hat);

    /**
     * The cross product of vectors can be represented as a matrix
     * multiplication operation. This function obtains the `3x3` matrix
     * of the cross-product operator from the first vector.
     * @f[\begin{align*}
     * \left(\vec{a}\times\right)\vec{b} &= \tilde{A}_a\vec{b}\\
     * \tilde{A}_a &=
     * \begin{bmatrix}0&-a_z&a_y\\a_z&0&-a_x\\-a_y&a_x&0\end{bmatrix}
     * \end{align*}@f]
     * @param[in] a input vector
     * @param[out] A the `3x3` matrix for the cross product operator
     * @f$\left(\vec{a}\times\right)@f$
     */
    void get_cross_matrix(const vec_3d *a, mat_3x3 *A);

    /** @} */

    /** @addtogroup quats 3D Quaternion operations
     * @{
     */
    /** a Quaternion type */
    typedef struct quaternion_
    {
        float w;     /**< real part of quaternion */
        vec_3d dual; /**< dual part of quaternion also a 3D vector */
    } quaternion;

    /** @} */

    /** @addtogroup dual_quats 3D Quaternion operations
     * @{
     */
    /** a dual quaternion type */
    typedef struct dual_quat_
    {
        quaternion real; /**< real part of dual quaternion */
        quaternion dual; /**< dual part of dual quaternion */
    } dual_quat;

#ifdef __cplusplus
}
#endif

/** @} */

#endif  // __LIBQUAT_H_