#include "position.h"
#include <math.h>
#include <QString>
#include <map>
#include <set>
#include <list>
#include "orient_map.h"
#include "orientation_server.h"
#ifndef ORIENT_H
#define ORIENT_H 1

  

class orient_cube: public position{
  public:
    orient_cube();
    orient_cube(position *p, int *o,orientation_server *s=0);
    orient_cube(orient_cube *ori);
    orient_cube(hypercube *h,orientation_server *s=0);
    ~orient_cube(){delete_all();}
    void delete_all();
   void delete_maps();
   void init_map_1d();
   void  transpose(int iax1,int iax2);
   int get_order(int iax){return order[iax];}
   void set_order(int iax,int i){ order[iax]=i;}
   void sync_pos(position *p);
   void center_it();
   void edge();
   void reset_it();
   bool get_reverse(int iax){ return reverse[iax];}
   void set_reverse(int iax,bool val){ this->reverse[iax]=val; 
    rotation_change();}
   void flip_axis(int iax){
      if(this->reverse[order[iax]]) this->reverse[order[iax]]=false;
      else this->reverse[order[iax]]=true;
    rotation_change();
    }
   virtual void update_extents();
   virtual void update_loc();
   void set_orders(int *ord){
   for (int i=0; i<8 ;i++) order[i]=ord[i]-1;}
   int get_end_o(int iax){return get_end(order[iax]);}
   void set_end_o(int iax,int i){set_end(order[iax],i);}
   int get_loc_o(int iax){return get_loc(order[iax]);}
   void get_orders(int *ord){for(int i=0; i<8; i++) ord[i]=order[i];}
   void form_index_map(int iax1, int iax2,bool r1, bool r2);
   void shift_data_image(int iax1, int iax2, float *locs){
     int i3a=0,i3b=0;
     rot_maps[form_map_name(iax1,iax2,0,&i3a,&i3b)]->shift_data_image(locs);
   }
   long long *get_index_map_ptr(int iax1,int iax2, int *n){
      int f1=get_beg(iax1),e1=get_end(iax1),f2=get_beg(iax2),e2=get_end(iax2);
      *n=(e1-f1)*(e2-f2);
      return get_index_map_ptr(iax1,iax2,f1,e1,f2,e2,0);
   }

   long long *get_index_map_ptr(int iax1,int iax2,int f1, int e1, int f2, int e2,int ioff);
   int form_map_name(int iax1,int iax2,int idelta,int *i3a, int *i3v);
   float get_rot_angle() {return ang*45/atan(1.);}
   void set_rot_angle(float a){ ang=a/45.*atan(1.);set_rotation();}
   void set_rotation();
   void set_rot_pt(int *pt){ memcpy(rot_pt,pt,8*sizeof(int)); set_rotation();}
   void get_rot_pt(int *pt){ memcpy(pt,rot_pt,8*sizeof(int));}
   void set_no_rotate();
   void get_rot_axes(int *a1, int *a2){ *a1=rot_ax[0]; *a2=rot_ax[1];}
   axis get_orient_axis(int iax){
      if(!rotate) return get_axis(iax);
      if(iax==rot_ax[0]) return ax_rot[0];
      if(iax==rot_ax[1]) return ax_rot[1];
      return get_axis(iax);
   }
   
   std::vector<int> return_picks_index(int iax1, int iax2, int idelta,QString col){
     int i3a=0,i3b=0;
     return rot_maps[form_map_name(iax1,iax2,idelta,&i3a,&i3b)]->return_picks_index(col);
  }


void set_picks(int iax1, int iax2, int idelta,picks_vec *pks){
  int i3a=0,i3b=0;
rot_maps[form_map_name(iax1,iax2,idelta,&i3a,&i3b)]->set_picks(pks);
}
void add_pick(int iax1, int iax2, int idelta,QString col, long long index){
  int i3a=0,i3b=0;

rot_maps[form_map_name(iax1,iax2,idelta,&i3a,&i3b)]->add_pick(col,index);

}
void del_pick(int iax1, int iax2, int idelta,QString col, long long index){
  int i3a=0,i3b=0;

 rot_maps[form_map_name(iax1,iax2,idelta,&i3a,&i3b)]->del_pick(col,index);
}
   
   
   void set_rot_axes (int a1, int a2);
   void find_rot_pair(int iax,int *ip,int *i);
   void get_rot_range(int iax, int *ib, int *ie);
   void get_axis_range(int iax, int *b, int *e);
   inline void rotate_pt(float x1, float x2, float *y1, float *y2){
    *y1=(x1-rot_cen[0])*cos(ang)+sin(ang)*(x2-rot_cen[1])+rot_cen[0];
    *y2=-(x1-rot_cen[0])*sin(ang)+cos(ang)*(x2-rot_cen[1])+rot_cen[1];
   }
   void convert_picks(picks_vec *in, picks_vec *out){
     for(int i=0; i < in->return_size();i++) out->add_pick(convert_pick(in->return_pick(i)));
   }
   inline pick_new *convert_pick(pick_new *in){
      axis a1=get_axis(rot_ax[0]),a2=get_axis(rot_ax[1]);
      float xin=in->iloc[rot_ax[0]]*a1.d+a1.o,yin=a2.o+a2.d*in->iloc[rot_ax[1]],xout,yout;
      rotate_pt(xin,yin,&xout,&yout);
      pick_new *out=in->clone();

      out->iloc[rot_ax[0]]=std::max(0,std::min(ax_rot[0].n-1,(int)(0.5+(xout-ax_rot[0].o)/ax_rot[0].d)));
      out->iloc[rot_ax[1]]=std::max(0,std::min(ax_rot[1].n-1,(int)(0.5+(yout-ax_rot[1].o)/ax_rot[1].d)));

      loc_to_index(out->iloc,&(out->pos));
      return out;
   }
   void form_hash_map(int iax1, int b1, int e1, int iax2, int b2, int e2, 
     std::vector<QString> *phash);
  
   void form_maps();
   axis get_rot_axis(int iax);
   inline void rotate_pt_back(float x1, float x2, float *y1, float *y2){
    *y1=(x1-rot_cen[0])*cos(-ang)+sin(-ang)*(x2-rot_cen[1])+rot_cen[0];
    *y2=-(x1-rot_cen[0])*sin(-ang)+cos(-ang)*(x2-rot_cen[1])+rot_cen[1];
   }
  void rotation_change(){
    for(int i=0; i< (int)rot_maps.size();i++) delete rot_maps[i];
      rot_maps.clear();
      map_order.clear();
      orient_num=serv->get_new_num(orient_num,rot_ax,ax_rot,ang,rot_cen);
  }
  
  int get_orient_num(){ return orient_num;}
  void update_map_order(int inum,bool newe);
  void load_map_1d();
  void set_one_shift(int iax, int *buf);
  int *return_one_shift(){return one_shift;}
  void orient_data_loc(int iax1, int iax2, int *iloc_old);
    void rotation_to_grid_loc(int iax1,int iax2, int *iloc_old);

  std::map<long long, int> *get_rot_map(int iax1, int iax2, int *n1);
   bool get_rotate(){return rotate;}
       int rot_ax[2];
    axis ax_rot[2];
    int **rot_to_reg_1;
    int **rot_to_reg_2;
  private:
    std::list<int>  map_order;
    int *one_shift;
    long long n123;
    int shift_ax;
    int order[8];
    int blocks[8];
    int b_rot[2],e_rot[2];
    bool reverse[8];
    bool rotate;
    float ang;
    int rot_pt[8];
    int *begs,*ends;
  //  int  **map_1d;
    float rot_cen[2];
    std::map<int,orient_map*> rot_maps;
    bool rev1,rev2,init;
    orientation_server *serv;
    int orient_num;
};
  

#endif
