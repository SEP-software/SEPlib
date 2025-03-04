#include "cgstep.h"
#include<math.h>
#include <iostream>
void cgstep::alloc_step(my_vector *mod, my_vector *dat){


  s=mod->clone_vec();
  ss=dat->clone_vec();

  forget_it();
 

}
bool cgstep::step_it(my_vector *m, my_vector *g, my_vector *rr, my_vector *gg){
  double alfa,beta;
  if(forget){
     beta=0;
     double gg_gg=gg->dot(gg);
     if(fabs(gg_gg)<
     small) {
        fprintf(stderr,"gg.dot(gg)==%g\n",gg_gg);
        return false;
     }
     alfa=-gg->dot(rr)/gg_gg;
  }
  else{
    double gg_gg=gg->dot(gg);
    double ss_ss=ss->dot(ss);
    double gg_ss=gg->dot(ss);
    if(fabs(gg_gg) < small || fabs(ss_ss) < small){
      fprintf(stderr,"gg.dot(gg)==0 or ss.dot(ss)==0\n");
     return false;
    }
    double determ=gg_gg*ss_ss*(1.0-gg_ss/gg_gg*gg_ss/ss_ss);
    double gg_rr=-gg->dot(rr);
    double ss_rr=-ss->dot(rr);
    alfa=( ss_ss*gg_rr-gg_ss*ss_rr)/determ;

       
    beta=(-gg_ss*gg_rr+gg_gg*ss_rr)/determ;

  }

 
  std::cout <<alfa<<"=alpha beta="<<beta<<std::endl;
  s->scale_add(beta,g,alfa);
  
  ss->scale_add(beta,gg,alfa);

  m->add(s);
 
  rr->add(ss);
 
 
  forget=false;
  return true;

}
