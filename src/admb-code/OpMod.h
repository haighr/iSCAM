/**
* \file OpMod.h
* \bief This is the operating model code for the population reference model.
* \author Steve Martell
* \date Jun 4, 2013
*
* DETAILED DESCRIPTION OF THE CLASS OperatingModel
*  - There is a single constructor that takes two arguments which are the
*    structs fro the data types (s_iSCAMdata), and the variable types 
*    (s_iSCAMvariables).  Once instantiated, a few of the methods of the 
*    OperatingModel class executed to initialize variables that are used 
*    in the main routines of the OperatingModel class.
* 
*/


// |---------------------------------------------------------------|
// | Structures for constants used in the general operating model. |
// |---------------------------------------------------------------|
#ifndef _SCENARIO_DATA_H
#define _SCENARIO_DATA_H

/** \brief  Structure for operating model constants
  \author  Steven Martell
  \author $LastChangedBy$
  \date `date +%Y-%m-%d`
  \date $LastChangedDate$
  \version $Rev$  \sa
**/
struct s_iSCAMdata
{
  // |------------------|
  // | Model dimensions |
  // |------------------|
  int nStock;               //!< Number of stocks
  int nArea;                //!< Number of management areas
  int nSex;                 //!< Number of distinct sexes in population
  int nSyr;                 //!< Initial year
  int nNyr;                 //!< Terminal year of available data
  int nPyr;                 //!< Terminal year of the projection period
  int nSage;                //!< Initial age class (years)
  int nNage;                //!< Terminal plus group age class (years)
  int nGear;                //!< Number of distinct fleets incl. survey vessels
  int nFleet;               //!< Number of fishing fleets with allocation > 0.

  dvector dAllocation;
  ivector nFleetIndex;

  // Growth & Maturity data
  dvector d_linf;
  dvector d_vonbk;
  dvector d_to;
  dvector d_a;
  dvector d_b;
  dvector d_ah;
  dvector d_gh;

  // Catch Data
  int     nCtNobs;
  dmatrix dCatchData;

  // Survey data
  int      nIt;
  ivector  nItNobs;
  ivector  nSurveyType;
  d3_array* dSurveyData;

  // Composition data
  int      nAgears;
  ivector  nAnobs;
  ivector  nAsage;
  ivector  nAnage;
  d3_array* dA;

  // Empirical weight-at-age
  int      nWtNobs;
  d3_array* dWt_avg;
  d3_array* dWt_mat;

  // control vector;
  dvector cntrl;

  
};
#endif




// |----------------------------------------------------------------------------|
// | Structure for variable parameters that define the operating model dynamics |
// |----------------------------------------------------------------------------|
#ifndef _SCENARIO_PARAMETERS_H
#define _SCENARIO_PARAMETERS_H
struct s_iSCAMvariables 
{
  /* Parameters used in the constructor */
  dvector   d_log_ro;
  dvector   d_steepness;
  dvector   d_log_m;
  dvector   d_log_rbar;
  dvector   d_log_rinit;
  dvector   d_rho;
  dvector   d_varphi;
  dvector   dLog_M_devs;
  dmatrix   dLog_Rbar_devs;
  dmatrix   dLog_Rinit_devs;

  /* Selectivity parameters */
  ivector   nSel_type;
  imatrix   nSel_block;
  d3_array* dSelPars;
  d4_array* d4_log_sel;

  
  /* Mortality rate arrays */
  d3_array* d3_Ft;
  d3_array* d3_Mt;
  d3_array* d3_St;


};
#endif









// |--------------------------------------------------|
// | Class definition for the general operating model |
// |--------------------------------------------------|
#ifndef OPERATINGMODEL_H
#define OPERATINGMODEL_H
class OperatingModel 
{
private:
  // |-----------------|
  // | Model constants |
  // |-----------------|
  
  int nStock;        
  int nArea;
  int nSex;
  int nSyr;
  int nNyr;
  int nPyr;
  int nSage;
  int nNage;
  int nGear;
  int nFleet;

  // LINKS TO MANAGE ARRAY INDEXING
  int n_ags;
  int n_ag;
  int n_gs;
  ivector n_area;
  ivector n_group;
  ivector n_sex;
  imatrix pntr_ag;
  imatrix pntr_gs;
  d3_array pntr_ags;

  dvector dAllocation;
  ivector nFleetIndex;


  dvector dAge;
  // Growth & Maturity data
  dvector d_linf;
  dvector d_vonbk;
  dvector d_to;
  dvector d_a;
  dvector d_b;
  dvector d_ah;
  dvector d_gh;

  // Catch Data
  int     nCtNobs;
  dmatrix dCatchData;

  d3_array d3_Ct;

  // Survey data
  int       nIt;
  ivector   nItNobs;
  ivector   nSurveyType;
  d3_array  dSurveyData;

   // Composition data
  int      nAgears;
  ivector  nAnobs;
  ivector  nAsage;
  ivector  nAnage;
  d3_array dA;

   // Empirical weight-at-age
  int      nWtNobs;
  dmatrix  dWt_bar;
  dmatrix  dEt_bar;
  d3_array dWt_avg;
  d3_array dWt_mat;


  // Model variables
  dvector dRo;
  dvector dSteepness;
  dvector dM;
  dvector dAvgRec;
  dvector dInitRec;
  dvector dRho;
  dvector dVartheta;
  dvector dLog_m_devs;
  dmatrix dLog_rbar_devs;
  dmatrix dLog_init_rec_devs;

  dvector dKappa;
  dvector nCntrl;
  d3_array d3_Ft;
  d3_array d3_Mt;
  

  // Selectivity parameters
  ivector  nSel_type;
  imatrix  nSel_block;
  d3_array d3_selPars;
  d4_array d4_log_sel;
  d5_array d5_logSel;     // deprecate

  // derived variables for SRR 
  dvector m_kappa;
  dvector m_so;
  dvector m_beta;
  dvector m_dSbo;

  d3_array d3_Nt;
  d3_array d3_Zt;
  d3_array d3_St;
  d3_array d3_wt_avg;
  d3_array d3_wt_mat;


  // reference points
  dvector m_dFmsy;

  // stock assessment results
  dvector m_est_bo;
  dvector m_est_fmsy;
  dvector m_est_msy;
  dvector m_est_bmsy;
  dvector m_est_sbt;
  dvector m_est_bt;

  int m_nSeed;    /**< Random number seed */
protected:
  dvector m_dTac;
  dmatrix m_dFt;
  int     m_nCtNobs;
  dmatrix m_dCatchData;

public:
  // OperatingModel(Scenario &cScenario);
  OperatingModel(const s_iSCAMdata&  mse_data, const s_iSCAMvariables& mse_vars);
  

  ~OperatingModel();

  /* data */
  void initializeConstants(const s_iSCAMdata& cS);
  void initializeVariables(const s_iSCAMvariables& cS);
  void calcSelectivities();
  void runScenario(const int& seed);

protected:
  void calcStockRecruitment();
  void conditionReferenceModel();
  void calcReferencePoints();
  void calcTAC();
  void implementFisheries(const int& iyr);
  void updateReferencePopulation(const int& iyr);
  void generateStockAssessmentData(const int& iyr);
  void runStockAssessment();

};
#endif