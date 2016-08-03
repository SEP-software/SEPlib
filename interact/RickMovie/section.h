/*
section object definition
*/
#ifndef MOVIE_SECTION
#include "main.h"
#include "data.h"
#include "map.h"

#ifdef __cplusplus /* if C++, specify external linkage to C functions */
extern "C" {
#endif
void	SectionPlane (int across , int down , int deep , stryng program , stryng file);
void	SectionProfile (int across , int down , int deep , stryng program , stryng file);
void	SectionExtractCube (Map hmap , Map vmap , Map zmap , Map map4 , Map map5 , FBuffer buffer , int n1 , int n2 , int n3 , int hdir , int vdir , int zdir);
void	SectionExtractPlane (Map hmap , Map vmap , Map zmap , Map map4 , Map map5 , FBuffer buffer , int n1 , int n2 , int hdir , int vdir);
void	SectionExtractProfile (Map hmap , Map vmap , Map zmap , Map map4 , Map map5 , FBuffer buffer , int n3 , int zdir);
#ifdef __cplusplus /* if C++, end external linkage specification */
}
#endif
#define MOVIE_SECTION
#endif
