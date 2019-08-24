class VplotSingle {
	 public:
										      FILE* getHeadStream(){ return headStream;}
     int getHcloseDone(){ return hclose_done;}
     void setHcloseDone(const int h){ hclose_done=h;}
     void setHeadStream(const FILE *h) { headStream=h;}
static VplotSingle& Instance() {
static VplotSingle myInstance;
			                            return myInstance;
			                          }
			                                // delete copy and move constructors and assign operators
			                                  VplotSingle(VplotSingle const&) = delete;             // Copy construct
			                                    VplotSingle(VplotSingle&&) = delete;                  // Move construct
			                                      VplotSingle& operator=(VplotSingle const&) = delete;  // Copy assign
			                                        VplotSingle& operator=(VplotSingle &&) = delete;      // Move assign
			       //
			       //                                   // Any other public methods.
			       //
			                                           protected:
			                                             VplotSingle() {
			       //                                          // Constructor code goes here.
			                                                   }
			      
			                                                  ~VplotSingle() {
			                                                       // Destructor code goes here.
									       /  private:
			                                                         }
};
