#ifndef _H_MYFONCTION_
#define _H_MYFONCTION_

#include <vector>
#include <gtk/gtk.h>
#include <glib.h>
#include <glib/gprintf.h>

typedef enum {
    TWOD,
    ThreeD
} Implementation_t;
typedef struct {
    bool TwoD;
    bool ThreD;
    bool AvecFrottement;
    bool SansFrottement;
} Model;
typedef struct {
    bool StoS;
    bool CtoP;
    bool IL;
    bool IQ;
} Maillage;
typedef struct {
    bool Elasto_Plast;
    bool Elasti;
} Comportement;

typedef enum {
    AvecFrottement,
    SansFrottement
} Contact_t;

typedef enum {
    Elasti,                                                //comportement elestique
    Elasto_Plast                                        //comportement elsto_plastique
} Behavior_t;
typedef struct {
    Behavior_t                            type;                // Type du comportement
    float                                young ;
    float                                poisson;
} Behavior;
typedef struct {
    int        BMN;        double        VMN;
    int        BMT;        double        VMT;
    int        BCN;        double        VCN;
    int        BCT;        double        VCT;
} Load;
typedef enum {
    Linear,
    Quadratic
} interpolation_t;
typedef struct {
    float                                normal_augment;
    float                                tang_aug_scale_factor;
    float                                warning_dist;
} Mortar_param;

typedef struct {
    Implementation_t I;
    Contact_t C;
    Behavior B1;
    Behavior B2;
    interpolation_t IN;
    Mortar_param MP;
    double MN;
    double MT;
    double fric_coeff;
    int Incr;
    int Iter;
    int CutsX;    
    double ratio;
    int CutsY;
    int config;

} ThisModel;

std::string removeSpaces(std::string str);

void createMesh(std::string Path,double R,int n,int CutsX,int CutsY ,int config,int cas,double ratio,int I);

void rek_mkdir(std::string Path);

FILE* creat_file(std::string Path,std::string FileName);

int Add_file_in_the_end(std::string PathFSrc ,std::string FileNameSrc,std::string PathFDest,std::string FileNameDest );

std::string SForme(std::string str,int nbr);

std::string SimTitle(const ThisModel T_Model);

void modifier_base_de_donnees(std::string Path,std::string FileName,std::string mot_a_modifier, std::string nouveau_mot);

void Create_MED(const ThisModel T_Model);

GtkWidget * CreateWin(int tx,int ty,int argc, char ** argv);

void lancer(std::vector < int >& nbrIncr, std::vector < int >& nbrIter,std::vector < int >& Tmesh, std::vector < double >& MpNAug, std::vector < double >& MpTASFac, std::vector < double >& MpWDist, std::vector < double >& B1young, std::vector < double>& B1poisson, std::vector < double >& B2young, std::vector < double >& B2poisson, std::vector < double >& MN, std::vector < double >& MT, std::vector < double >& CN, std::vector < double >& CT);

void on_copier_button(GtkWidget *PButton, gpointer data);


void cb_activate (GtkEntry * p_entry, gpointer p_data) ;

template <typename T>

std::vector<T> extract(std::string s);


#endif
