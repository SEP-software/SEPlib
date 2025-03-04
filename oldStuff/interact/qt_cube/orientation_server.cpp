#include "orientation_server.h"
converter::converter(int *in,axis *ax,float a,float *cen,axis *una){
    rot_ax[0]=in[0]; rot_ax[1]=in[1];
    ax_rot[0]=ax[0]; ax_rot[1]=ax[1];
    ang=a;
    rot_cen[0]=cen[0];
    rot_cen[1]=cen[1];
    a1=una[0];
    a2=una[1];
  }
 pick_new *converter::convert_pick( pick_new *in){
      float xin=in->iloc[rot_ax[0]]*a1.d+a1.o;
      float yin=a2.o+a2.d*in->iloc[rot_ax[1]],xout=0,yout=0;
      rotate_pt(xin,yin,&xout,&yout);
      pick_new *out=in->clone();
      
   
      out->iloc[rot_ax[0]]=std::max(0,std::min(ax_rot[0].n-1,(int)(0.5+(xout-ax_rot[0].o)/ax_rot[0].d)));
      out->iloc[rot_ax[1]]=std::max(0,std::min(ax_rot[1].n-1,(int)(0.5+(yout-ax_rot[1].o)/ax_rot[1].d)));
   
      return out;
   }
 pick_new *converter::convert_back_pick( pick_new *in){
      float xin=in->iloc[rot_ax[0]]*a1.d+a1.o;
      float yin=a2.o+a2.d*in->iloc[rot_ax[1]],xout=0,yout=0;
      rotate_pt_back(xin,yin,&xout,&yout);
      pick_new *out=in->clone();
      
   
      out->iloc[rot_ax[0]]=std::max(0,std::min(ax_rot[0].n-1,(int)(0.5+(xout-ax_rot[0].o)/ax_rot[0].d)));
      out->iloc[rot_ax[1]]=std::max(0,std::min(ax_rot[1].n-1,(int)(0.5+(yout-ax_rot[1].o)/ax_rot[1].d)));
   
      return out;
   }
   
   
  void converter::rotate_pt_back(float x1, float x2, float *y1, float *y2){
   
    *y1=(x1-rot_cen[0])*cos(-ang)+sin(-ang)*(x2-rot_cen[1])+rot_cen[0];
    *y2=-(x1-rot_cen[0])*sin(-ang)+cos(-ang)*(x2-rot_cen[1])+rot_cen[1];

   }
     
  void converter::rotate_pt(float x1, float x2, float *y1, float *y2){
   
    *y1=(x1-rot_cen[0])*cos(ang)+sin(ang)*(x2-rot_cen[1])+rot_cen[0];
    *y2=-(x1-rot_cen[0])*sin(ang)+cos(ang)*(x2-rot_cen[1])+rot_cen[1];

   }
  
  orientation_server::orientation_server(position *pos){num=0; myp=pos;}

  int orientation_server::get_new_num(int iold,int *in, axis *ax, float a, float *cen){
    for(std::set<int>:: iterator i=active_list.begin(); i!=active_list.end(); i++){
       if(*i==iold) {
         active_list.erase(i); 
         if(converters.count(iold)==1) {
           delete converters[iold];
           converters.erase(iold);
         }
         int inew=get_new_num();

         axis una[2];

         una[0]=myp->get_axis(in[0]);

         una[1]=myp->get_axis(in[1]);

         converters[inew]=new converter(in,ax,a,cen,una);

         return inew;
       }
    }
    return iold; // something wrong here.
  }
  pick_new *orientation_server::convert_pick(int oc,pick_new *pk){
      if(converters.count(oc)==1){
         pick_new *p= converters[oc]->convert_pick(pk);
         myp->loc_to_index(p->iloc,&(p->pos));
         return p;
         }
       
        return pk->clone();
      
  }
  pick_new *orientation_server::convert_back_pick(int oc,pick_new *pk){
      if(converters.count(oc)==1){
         pick_new *p= converters[oc]->convert_back_pick(pk);
         myp->loc_to_index(p->iloc,&(p->pos));
         return p;
         }
       
        return pk->clone();
      
}
