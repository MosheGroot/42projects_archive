#include "render.h"

t_obj   *check_intersection(const t_crd *origin, const t_crd *ray,
                            const t_list *objects, double *t)
{
    t_obj   *obj;
    double  t_tmp;

    obj = NULL;
    *t = INFINITY;
    while (objects)
    {
        t_tmp = ((t_obj *)objects->data)->get_inters_func(origin, ray,
                objects->data);
        if (t_tmp > 0 && t_tmp < *t)
        {
            *t = t_tmp;
            obj = (t_obj *)objects->data;
        }
        objects = objects->next;
    }
    return (obj);
}

static t_light  get_light_2(const t_crd *origin, const t_crd *normal,
                            const t_light *light, const t_scene *scene)
{
    t_crd   ray;
    t_light out;
    double  light_dist;
    double  t;

    out.br = 0;
    out.col = color_get_default();
    ray = vec_get(*origin, light->pos);
    light_dist = vec_module(ray);
    ray = vec_normalize(ray);
    if (!check_intersection(origin, &ray, scene->objs, &t)
        || t > light_dist)
    {
        t = vec_dot(ray, *normal) * light->br;
        out.col = color_mul(light->col, fabs(t));
        out.br = fabs(t);
    }
    return (out);
}

t_light     get_light(t_crd *origin, t_crd normal, const t_scene *scene)
{
    t_light out;
    t_light tmp;
    t_list  *lights;

    out.br = 0;
    out.col = color_get_default();
    lights = scene->lights;
    while (lights)
    {
        tmp = get_light_2(origin, &normal, ((t_light *)lights->data), scene);
        out.br += tmp.br;
        out.col = color_add(out.col, tmp.col);
        lights = lights->next;
    }
    out.br += scene->amb_coeff;
    out.col = color_add(out.col, color_mul(scene->amb_col, scene->amb_coeff));
    return (out);
}
