#ifndef TYPE3TOPTAGGER_H
#define TYPE3TOPTAGGER_H 

#include <memory>

#include "recipeAUX/OxbridgeMT2/interface/Basic_Mt2_332_Calculator.h"
#include "recipeAUX/OxbridgeMT2/interface/ChengHanBisect_Mt2_332_Calculator.h"

#include "combination.h"
#include "indexSort.h"

#include "TTree.h"
#include "TLorentzVector.h"

#include <vector>
#include <map>

namespace topTagger{

   using namespace stdindexSort;
   using namespace stdcomb;
   using namespace std;

   typedef unsigned int size;
   typedef std::vector<int>::iterator vii;

   const std::string defaultOrderingOptArr[] = {"mass", "mass"};
   const int defaultMaxIndexForOrderingArr[] = { 1,         1 };

   const double minCSVS_disablebtag = -1e10;
   const double maxEta_disablebtag = 99.0;

   class type3TopTagger {

      public:

//         type3TopTagger();
         ~type3TopTagger();

// Make these variables public so that they can be easily accessed
// They should be actually internal and/or intermediate variables
// The better way is to make a get function for each of them, 
// but then there will be so many of them...
// DON'T OVERRIDE THEM!
         bool isTopEvent;
         vector<vector<int> > finalCombfatJets; vector<vector<int> > finalRemaining; vector<vector<vector<int> > > finalCombJetSubStruc;
         vector<double> fatJetMassVec; vector<vector<double> > fatJetSubMassVec;
         vector<double> finalCombMaxDR;
         int cntnbJetsCSVS;
         int combSize;
         vector<vector<int> > finalCombfatJetsPassStatusVec;
         vector<int> cntTopCandPassCSVSVec, cntRemainingPassCSVSVec;
         int nTopJetCandCnt, nTopJetCandWithBtagCnt;
         int bestTopJetIdx;

         vector<int> allCombPassCriteriaVec;
         
         double bestTopJetMass;
         vector<int> bestTopJetComb;
         vector<vector<int> > bestTopJetSubStruc;
         vector<int> remainTopJetComb;
         int remainJetNum;
         TLorentzVector bestTopJetLVec;
         vector<double> bestSubMassVec;
      
         double bestCloseTomW;
         TLorentzVector bestCloseTomWLVec, bestbJetLVec;
      
         bool remainPassCSVS;
         vector<int> pickedbTaggedJetIdxVec;
         int pickedbTaggedJetIdx; double maxCSVS;
         bool bestPassCSVS;
         vector<int> pickedbTaggedbestTopJetIdxVec;
      
         vector<vector<int> > finalRemainingCombfatJets; vector<vector<int> > finalRemaining2; vector<vector<vector<int> > > finalRemainingCombJetSubStruc;
         vector<double> finalRemainingCombMaxDR;
         int pickedRemainingCombfatJetIdx; double pickedRemainingCombfatJetMass;
         int pickedRemainingCombfatJetbJetIdx;
         int cntbTaggedIndex;
      
         vector<int> pickedRemainingCombfatJet; vector<vector<int> > pickedRemainingCombJetSubStruc;
      
         TLorentzVector remainingTopJetLVec;
         double pickedRemainingfatJetMass;
         vector<double> pickedRemainingSubMassVec;
      
         double pickedRemainingCloseTomW;
      
         vector<int> pickedRemainingmxyPair;
         double pickedRemainingmxy;
         TLorentzVector pickedRemainingbJetLVec;
      
         int pickedClosestJetTobIdx; double pickedClosestJetTobDeltaR;

         TLorentzVector pickedRemainingbJetPlusAJetLVec;
         
         double mTbestTopJet; 
         double mTbestWJet, mTbestbJet;
         
         double mTremainingTopJet;
         
         double closemT;
         
         int closebJetIdx; double closebJetDphi; TLorentzVector closebJetLVec;
         double mTbJet;
         
         double MT2;
// For HepTopTagger
         std::vector<TLorentzVector> modiforiJetsVec; std::vector<double> modifrecoJetsBtagCSVS;

// For groomed jets
         std::vector<TLorentzVector> groomedJetsVec_;

// For top candidate counting
         std::map<double, std::vector<int> > topJetCand_deltaM_idx123Map;
         std::vector<int> allIdxCacheVec;
         std::vector<int> pickedTopCandSortedVec;
         int nTopCandSortedCnt;
// End of internal and/or intermediate variables

/* 
// Please add function pre-declaration here for quick look-up
// FIXME: Currently make all function inline to avoid "multiple definition" link errors

         void setDefaultVars();

// The functions driving the topTagger procedure
         void prepareFindingBestTopCandidate(const std::vector<TLorentzVector> &oriJetsVec, const std::vector<double> &recoJetsBtagCSVS);
         void findBestTopCandidate(const std::vector<TLorentzVector> &oriJetsVec, const std::vector<double> &recoJetsBtagCSVS);
         void fillingBestTopCandidateVars(const std::vector<TLorentzVector> &oriJetsVec, const std::vector<double> &recoJetsBtagCSVS);

         void findDiTopCandidates(const std::vector<TLorentzVector> &oriJetsVec, const std::vector<double> &recoJetsBtagCSVS);

         void prepareFindingRemainingTopCandidate(const std::vector<TLorentzVector> &oriJetsVec, const std::vector<double> &recoJetsBtagCSVS);
         void findRemainingTopCandidate(const std::vector<TLorentzVector> &oriJetsVec, const std::vector<double> &recoJetsBtagCSVS);
         void fillingRemainingTopCandidate(const std::vector<TLorentzVector> &oriJetsVec, const std::vector<double> &recoJetsBtagCSVS);
       
         void tunningRemainingJetSystem(const std::vector<TLorentzVector> &oriJetsVec, const std::vector<double> &recoJetsBtagCSVS, const TLorentzVector &metLVec);
      
         void prepareCutVariables(const std::vector<TLorentzVector> &oriJetsVec, const std::vector<double> &recoJetsBtagCSVS, const TLorentzVector &metLVec);
         
         bool applyCuts();

// For HEPTopTagger
         void resolveOverlappingJets(const std::vector<TLorentzVector> &oriJetsVec, const std::vector<double> &recoJetsBtagCSVS, const std::vector<TLorentzVector> &hepTaggerSubJetsVec, std::vector<int> &tmpremainingJetsVec, std::vector<double> &tmpremainingJetsBtagCSVS, std::vector<double> &hepTaggerSubJetsBtagCSVS);
         void prepareANDfindBestTopCandidate(const std::vector<TLorentzVector> &oriJetsVec, const std::vector<double> &recoJetsBtagCSVS, const std::vector<std::vector<TLorentzVector> > &hepTaggerJetsVec, std::vector<TLorentzVector> &tmpModiforiJetsVec, std::vector<double> &tmpModifrecoJetsBtagCSVS);

// The master function to incorporate all functions in one place
        // The runOnlyTopTaggerPart is used for only top tagger part. Disentangle the top tagger part with the b tagging part.
        // It is the same as dobVetoCS==true where no b jets are defined. The only difference is that both the b jet CSV and 
        // _eta_ requirement are relaxed.
         void runOnlyTopTaggerPart(const std::vector<TLorentzVector> &oriJetsVec, const std::vector<double> &recoJetsBtagCSVS);
         int findnTopCands(const std::vector<TLorentzVector> &oriJetsVec);
         bool processEvent(const std::vector<TLorentzVector> &oriJetsVec, const std::vector<double> &recoJetsBtagCSVS, const TLorentzVector &metLVec);
         bool processEvent(const std::vector<TLorentzVector> &oriJetsVec, const std::vector<double> &recoJetsBtagCSVS, const TLorentzVector &metLVec, const std::vector<std::vector<TLorentzVector> > &hepTaggerJetsVec);

// The very basic function faciliating the triplet making and variable calculation
         void buildOneFatJetsIndexComb(vector<int> indexVec, vector<int> &iniIndexComb, vector<vector<int> > &tmpFinalCombJets, vector<vector<int> > &tmpFinalRemaining);
         void buildSubStrucIndexComb(vector<int> indexVec, vector<vector<int> > &tmpFinalCombSubStruc);
         TLorentzVector buildLVec(const vector<TLorentzVector> &oriJetsVec, const vector<int> &indexCombVec);
         void calcSubStrucMass(const vector<TLorentzVector> &oriJetsVec, const vector<vector<int> > &tmpFinalCombSubStruc, vector<double> &tmpFinalSubStrucMass);
         bool filterfatJetWithDRcone(const vector<TLorentzVector> &oriJetsVec, const vector<int> &indexCombVec, const double drCut);
// The passStatusVec is used to pass flags on what mass criteria should be checked.
// Default is passStatusVec is empty and all mass criteria are checked.
         int checkTopCriteria(const std::vector<int> &perCombfatJets, const std::vector<TLorentzVector> &oriJetsVec, const std::vector<double> &recoJetsBtagCSVS, const vector<double> &tmpFinalSubStrucMass, const double &fatJetMass, vector<int> &passStatusVec);
         void prepareCombination(const vector<int> &indexVec, vector<vector<int> > &tmpFinalCombfatJets, vector<vector<int> > &tmpFinalRemaining, vector<vector<vector<int> > > &tmpFinalCombJetSubStruc);
         void ptOrderedfatJets(const vector<TLorentzVector> &oriJetsVec, vector<vector<int> > &tmpFinalCombfatJets, vector<vector<int> > &tmpFinalRemaining, vector<vector<vector<int> > > &tmpFinalCombJetSubStruc);
         void onlyfatJetsCloseInACone(const vector<int> &indexVec, const vector<TLorentzVector> &oriJetsVec, const std::vector<double> &recoJetsBtagCSVS, vector<vector<int> > &tmpFinalCombfatJets, vector<vector<int> > &tmpFinalRemaining, vector<vector<vector<int> > > &tmpFinalCombJetSubStruc);
         double calcMT2(const TLorentzVector &fatJet1LVec, const TLorentzVector &fatJet2LVec, const TLorentzVector &metLVec); 
         double calcMT(const TLorentzVector &objLVec, const TLorentzVector &metLVec);
         void makeWjetfatJets(const vector<TLorentzVector> &oriJetsVec, const std::vector<double> &recoJetsBtagCSVS, vector<vector<int> > &tmpFinalCombfatJets, vector<vector<int> > &tmpFinalRemaining, vector<vector<vector<int> > > &tmpFinalCombJetSubStruc);
         void makeTopjetfatJets(const vector<TLorentzVector> &oriJetsVec, const std::vector<double> &recoJetsBtagCSVS, vector<vector<int> > &tmpFinalCombfatJets, vector<vector<int> > &tmpFinalRemaining, vector<vector<vector<int> > > &tmpFinalCombJetSubStruc);
*/

         type3TopTagger(){
            mWoverTop_ = -1; lowRatioWoverTop_ = -1; highRatioWoverTop_ = -1;
            setdoExtraCuts(true);
            setdoInvertTopCriteria(false);
            setmTbcut(500);
            setmTtcut(365);
            setMT2cut(300);
            setmTWcut(600);
            setdoMTMT2cuts(true);
            setPDGmWmTop(80.385, 173.5);
            setlowRatioWoverTop(0.85);
            sethighRatioWoverTop(1.25);
            setlowArcTanm13overm12(0.2);
            sethighArcTanm13overm12(1.3);
            setlowm23overm123(0.35);
            setdefaultJetCone(2.0);
            setsimuCAdeltaR(1.5);
            setsimuCALargerdeltaR(-1);
            setlowTopCut(80);
            sethighTopCut(270);
            setlowWCut(50);
            sethighWCut(120);
            setCSVS(0.814);
            setnSubJetsDiv(3);
            setnJetsSel(5);
            setmaxEtaForbJets(2.4);
            setorderingOptArr();
            setmaxIndexForOrderingArr();
            setmaxDRjetMatch(0.3);
            setdebug(true);
            settaggingMode(false);

            setdobVetoCS(false);

            setdoTopVeto(false);

            setbVetoMethod(0);

            setWjetMassRanges(70, 110);
            setdoWjetfatJets(true);

            setTopjetMassRanges(130, 220);
            setdoTopjetfatJets(true);
 
            setdoCombTopTagger(false);
            setlowTopPtToComb(150);

            setDefaultVars();

            groomedJetsVec_.clear();
         }

         void setDefaultVars(){

            isTopEvent = false;
            finalCombfatJets.clear(); finalRemaining.clear(); finalCombJetSubStruc.clear();
            fatJetMassVec.clear(); fatJetSubMassVec.clear();
            finalCombMaxDR.clear();
            cntnbJetsCSVS = 0;
            combSize = -1;
            finalCombfatJetsPassStatusVec.clear();
            cntTopCandPassCSVSVec.clear(); cntRemainingPassCSVSVec.clear();
            nTopJetCandCnt = 0; nTopJetCandWithBtagCnt =0;
            bestTopJetIdx = -1;
 
            allCombPassCriteriaVec.clear();
               
            bestTopJetMass = -1;
            bestTopJetComb.clear(); bestTopJetSubStruc.clear();
            remainTopJetComb.clear();
            remainJetNum = -1;
            bestSubMassVec.clear();
               
            bestCloseTomW = -1;
            
            remainPassCSVS = false; pickedbTaggedJetIdxVec.clear();
            pickedbTaggedJetIdx = -1; maxCSVS = -1;
            bestPassCSVS = false; pickedbTaggedbestTopJetIdxVec.clear();
         
            finalRemainingCombfatJets.clear(); finalRemaining2.clear(); finalRemainingCombJetSubStruc.clear();
            finalRemainingCombMaxDR.clear();
            pickedRemainingCombfatJetIdx = -1; pickedRemainingCombfatJetMass = -1;
            pickedRemainingCombfatJetbJetIdx = -1;
            cntbTaggedIndex = -1;
              
            pickedRemainingCombfatJet.clear(); pickedRemainingCombJetSubStruc.clear();
              
            pickedRemainingfatJetMass = -1; pickedRemainingSubMassVec.clear();
              
            pickedRemainingCloseTomW = -1;
         
            pickedRemainingmxyPair.clear();
            pickedRemainingmxy = -1;
         
            pickedClosestJetTobIdx = -1; pickedClosestJetTobDeltaR = -1;
         
            mTbestTopJet = -1;
            mTbestWJet = -1, mTbestbJet = -1;
         
            mTremainingTopJet = -1;
         
            closemT = -1;
         
            closebJetIdx = -1; closebJetDphi = -1;
            mTbJet = -1;
         
            MT2 = -1;

            modiforiJetsVec.clear(); modifrecoJetsBtagCSVS.clear();

            topJetCand_deltaM_idx123Map.clear();
            allIdxCacheVec.clear();
            pickedTopCandSortedVec.clear();
            nTopCandSortedCnt = 0;
         }

         void buildOneFatJetsIndexComb(vector<int> indexVec, vector<int> &iniIndexComb, vector<vector<int> > &tmpFinalCombJets, vector<vector<int> > &tmpFinalRemaining){

            tmpFinalCombJets.clear(); tmpFinalRemaining.clear();

            vector<vector<int> > combHolder;

            do{
               combHolder.push_back(iniIndexComb);
            }while(next_combination(indexVec.begin(),indexVec.end(),iniIndexComb.begin(),iniIndexComb.end()) );

            unsigned int tmpCombSize = combHolder.size();
            for(unsigned int ic=0; ic<tmpCombSize; ic++){
               tmpFinalCombJets.push_back(combHolder[ic]);
               tmpFinalRemaining.push_back(indexVec);
               for(vii it=tmpFinalCombJets.back().begin(); it!=tmpFinalCombJets.back().end(); it++){
                  vii jt = find(tmpFinalRemaining.back().begin(), tmpFinalRemaining.back().end(), (*it));
                  if( jt!= tmpFinalRemaining.back().end() ) tmpFinalRemaining.back().erase(jt);
               }
            }
         }

         void buildSubStrucIndexComb(vector<int> indexVec, vector<vector<int> > &tmpFinalCombSubStruc){
         
            tmpFinalCombSubStruc.clear();
         
            if( indexVec.size() <=2 ){ tmpFinalCombSubStruc.push_back(indexVec); return; }
         
            vector<int> iniIndexVec; iniIndexVec.push_back(indexVec[0]); iniIndexVec.push_back(indexVec[1]);
         
            do{
               tmpFinalCombSubStruc.push_back(iniIndexVec);
            }while(next_combination(indexVec.begin(),indexVec.end(),iniIndexVec.begin(),iniIndexVec.end()) );
         
         }

         TLorentzVector buildLVec(const vector<TLorentzVector> &oriJetsVec, const vector<int> &indexCombVec){
         
            TLorentzVector combLVec;
            for(unsigned int ic=0; ic<indexCombVec.size(); ic++){
               int idx = indexCombVec[ic];
               combLVec += oriJetsVec[idx];
            }
            return combLVec;
         }

         void calcSubStrucMass(const vector<TLorentzVector> &oriJetsVec, const vector<vector<int> > &tmpFinalCombSubStruc, vector<double> &tmpFinalSubStrucMass){
            tmpFinalSubStrucMass.clear();
            for(unsigned int is=0; is<tmpFinalCombSubStruc.size(); is++){
               double perMass = buildLVec(oriJetsVec, tmpFinalCombSubStruc[is]).M();
               tmpFinalSubStrucMass.push_back(perMass);
            }
         }

         bool filterfatJetWithDRcone(const vector<TLorentzVector> &oriJetsVec, const vector<int> &indexCombVec, const double drCut){
            if( drCut == -1 ) return true;

            bool withinCone = true;
            TLorentzVector centralLVec = buildLVec(oriJetsVec, indexCombVec);
            for(unsigned int ic=0; ic<indexCombVec.size(); ic++){
               int idx = indexCombVec[ic];
               double deltaR = centralLVec.DeltaR(oriJetsVec[idx]);
               if( deltaR > drCut ) withinCone = false;
            }
            return withinCone;
         }

         int checkTopCriteria(const std::vector<int> &perCombfatJets, const std::vector<TLorentzVector> &oriJetsVec, const std::vector<double> &recoJetsBtagCSVS, const vector<double> &tmpFinalSubStrucMass, const double &fatJetMass, vector<int> &passStatusVec){
         
            passStatusVec.clear();
            int passCriteria =0;

            int cntBtag = 0;
            // do not bypass cntBtag >=2 cases for top tagger efficiency measurement where
            // the btagging check is disabled (using a special way which can interfere here)!
            if( CSVS_ != minCSVS_disablebtag && maxEtaForbJets_ != maxEta_disablebtag ){
               for(unsigned int it=0; it<perCombfatJets.size(); it++){
                  int idx = perCombfatJets[it];
                  if( recoJetsBtagCSVS[idx] > CSVS_ && fabs(oriJetsVec[idx].Eta())<maxEtaForbJets_ ) cntBtag ++;
               }
            }

            // top quark rarely has >=2 b quarks in the decay!
            if( cntBtag >= 2 ){
               if( tmpFinalSubStrucMass.size() == 3 ){
                  for(unsigned int is=0; is<3; is++) passStatusVec.push_back(0);
               }else if( tmpFinalSubStrucMass.size() == 1 ){
                  passStatusVec.push_back(0);
               }else if( tmpFinalSubStrucMass.size() == 0 ){
                  passStatusVec.push_back(0);
               }
               // default is 0
               return passCriteria;
            }

            if( tmpFinalSubStrucMass.size() ==3 ){
               const double m12 = tmpFinalSubStrucMass[0], m13 = tmpFinalSubStrucMass[1], m23 = tmpFinalSubStrucMass[2];
               const double m123 = fatJetMass;
               // a) for Rmin_ < m23/m123 < Rmax_
               if(    TMath::ATan(m13/m12) > lowArcTanm13overm12_ && TMath::ATan(m13/m12) < highArcTanm13overm12_
                   && m23/m123 > Rmin_ && m23/m123 < Rmax_ ){
                  passCriteria = 1;
                  passStatusVec.push_back(1);
               }else{
                  passStatusVec.push_back(0);
               }
               // b) roughly Rmin_ < m12/m123 < Rmax_ && m23/m123 > 0.35
               if(     Rmin_*Rmin_ *(1+ (m13/m12)*(m13/m12)) < 1- (m23/m123)*(m23/m123)
                   &&  1-(m23/m123)*(m23/m123) < Rmax_*Rmax_*(1+(m13/m12)*(m13/m12) )
               // disable m23/m123 check for top veto case!
                   &&  ( doTopVetoSel_ || m23/m123 > lowm23overm123_) ){
                  passCriteria = 1;
                  passStatusVec.push_back(1);
               }else{
                  passStatusVec.push_back(0);
               }
               // c) roughly Rmin_ < m13/m123 < Rmax_ && m23/m123 > 0.35
               if(     Rmin_*Rmin_ *(1+ (m12/m13)*(m12/m13)) < 1- (m23/m123)*(m23/m123)
                   &&  1-(m23/m123)*(m23/m123) < Rmax_*Rmax_*(1+(m12/m13)*(m12/m13) )
               // disable m23/m123 check for top veto case!
                   &&  ( doTopVetoSel_ || m23/m123 > lowm23overm123_) ){
                  passCriteria = 1;
                  passStatusVec.push_back(1);
               }else{
                  passStatusVec.push_back(0);
               }
            }else if( tmpFinalSubStrucMass.size() ==1 ){
               const double m23 = tmpFinalSubStrucMass[0];
               const double m123 = fatJetMass;
               if( m23/m123 > Rmin_ && m23/m123 < Rmax_ ){
                  passCriteria = 1;
                  passStatusVec.push_back(1);
               }else{
                  passStatusVec.push_back(0);
               }
            }else if( tmpFinalSubStrucMass.size() ==0 ){
               passCriteria = 1;
               passStatusVec.push_back(1);
            }

            return passCriteria;

         }

         void prepareCombination(const vector<int> & indexVec, vector<vector<int> > &tmpFinalCombfatJets, vector<vector<int> > &tmpFinalRemaining, vector<vector<vector<int> > > &tmpFinalCombJetSubStruc){

            tmpFinalCombfatJets.clear(); tmpFinalRemaining.clear(); tmpFinalCombJetSubStruc.clear();

            if( nSubJetsDiv_ > (int)indexVec.size() ){ std::cout<<"indexVec.size : "<<indexVec.size()<<" is SHORTER than nSubJetsDiv_ : "<<nSubJetsDiv_<<"?!"<<std::endl; return; }

            vector<int> iniIndexComb; for(int ij=0; ij<nSubJetsDiv_; ij++) iniIndexComb.push_back(indexVec[ij]);

            buildOneFatJetsIndexComb(indexVec, iniIndexComb, tmpFinalCombfatJets, tmpFinalRemaining);

            unsigned int tmpCombSize = tmpFinalCombfatJets.size();

            for(unsigned int ic=0; ic<tmpCombSize; ic++){
               vector<vector<int> > perJetSub;

               buildSubStrucIndexComb(tmpFinalCombfatJets[ic], perJetSub); tmpFinalCombJetSubStruc.push_back(perJetSub);

            }
         }

         void ptOrderedfatJets(const vector<TLorentzVector> &oriJetsVec, vector<vector<int> > &tmpFinalCombfatJets, vector<vector<int> > &tmpFinalRemaining, vector<vector<vector<int> > > &tmpFinalCombJetSubStruc){
            const vector<vector<int> > cachedtmpFinalCombfatJets = tmpFinalCombfatJets;
            const vector<vector<int> > cachedtmpFinalRemaining = tmpFinalRemaining;
            const vector<vector<vector<int> > > cachedtmpFinalCombJetSubStruc = tmpFinalCombJetSubStruc;
         
            tmpFinalCombfatJets.clear(); tmpFinalRemaining.clear(); tmpFinalCombJetSubStruc.clear();
         
            unsigned int tmpCombSize = cachedtmpFinalCombfatJets.size();
         
// Get the index after pt ordered
            vector<double> tempfatJetPtVec;
            for(unsigned int ic=0; ic<tmpCombSize; ic++){ tempfatJetPtVec.push_back(buildLVec(oriJetsVec, cachedtmpFinalCombfatJets[ic]).Pt()); }
            std::vector<size_t> ptindexes;
            argsort(tempfatJetPtVec.begin(), tempfatJetPtVec.end(), std::greater<double>(), ptindexes);
         
// Transfer the fat jets to pt ordered
            for(unsigned int ii=0; ii<ptindexes.size(); ii++){
               unsigned int indexMapped = ptindexes[ii];
               tmpFinalCombfatJets.push_back( cachedtmpFinalCombfatJets[indexMapped] );
               tmpFinalRemaining.push_back( cachedtmpFinalRemaining[indexMapped] );
               tmpFinalCombJetSubStruc.push_back( cachedtmpFinalCombJetSubStruc[indexMapped] );
            }
         }

         void makeWjetfatJets(const vector<TLorentzVector> &oriJetsVec, const std::vector<double> &recoJetsBtagCSVS, vector<vector<int> > &tmpFinalCombfatJets, vector<vector<int> > &tmpFinalRemaining, vector<vector<vector<int> > > &tmpFinalCombJetSubStruc){
            tmpFinalCombfatJets.clear(); tmpFinalRemaining.clear(); tmpFinalCombJetSubStruc.clear();

            vector<int> tmpWjetIdx, tmpRemainIdx;

            std::vector<TLorentzVector> forJetMassLVec = oriJetsVec;
            if( !groomedJetsVec_.empty() ){
               if( groomedJetsVec_.size() == oriJetsVec.size() ){
                  forJetMassLVec = groomedJetsVec_;
               }else{
                  std::cout<<"\nWARNING ...   groomedJetsVec_.size : "<<groomedJetsVec_.size()<<"  NOT equal input oriJetsVec.size : "<<oriJetsVec.size()<<std::endl;
                  std::cout<<"reverting back to oriJetsVec for W mass determination! Please double-check the inputs!"<<std::endl<<std::endl;
               }
            }

            for(unsigned int ij=0; ij<oriJetsVec.size(); ij++){
               TLorentzVector perWjetLVec = forJetMassLVec[ij];
//               if( perWjetLVec.M() <= highWjetMass_ && perWjetLVec.M() >= lowWjetMass_ && recoJetsBtagCSVS[ij] <= CSVS_ ){
               if( perWjetLVec.M() <= highWjetMass_ && perWjetLVec.M() >= lowWjetMass_ ){
                  tmpWjetIdx.push_back(ij);
               }else{
                  tmpRemainIdx.push_back(ij);
               }
            }

// In the perComb, the first one is always the Wjet!
// And the subStruc mass is always the W mass and only the W mass, since
// in this case the only sub-structure is the W jet!
            for(unsigned int iw=0; iw<tmpWjetIdx.size(); iw++){
               for(unsigned int ir=0; ir<tmpRemainIdx.size(); ir++){
                  vector<int> perComb, perRemain;
                  perComb.push_back(tmpWjetIdx[iw]); perComb.push_back(tmpRemainIdx[ir]);
                  for(int ij=0; ij<(int)oriJetsVec.size(); ij++){
                     if( ij == tmpWjetIdx[iw] || ij == tmpRemainIdx[ir] ) continue;
                     perRemain.push_back(ij);
                  }
                  tmpFinalCombfatJets.push_back(perComb); tmpFinalRemaining.push_back(perRemain);
                  vector<vector<int> > perSubStruc;
                  vector<int> WjetSubStruc; WjetSubStruc.push_back(tmpWjetIdx[iw]);
                  perSubStruc.push_back(WjetSubStruc);
                  tmpFinalCombJetSubStruc.push_back(perSubStruc);
               }
            }
         }

         void makeTopjetfatJets(const vector<TLorentzVector> &oriJetsVec, const std::vector<double> &recoJetsBtagCSVS, vector<vector<int> > &tmpFinalCombfatJets, vector<vector<int> > &tmpFinalRemaining, vector<vector<vector<int> > > &tmpFinalCombJetSubStruc){
            tmpFinalCombfatJets.clear(); tmpFinalRemaining.clear(); tmpFinalCombJetSubStruc.clear();

            vector<int> tmpTopjetIdx, tmpRemainIdx;

            std::vector<TLorentzVector> forJetMassLVec = oriJetsVec;
            if( !groomedJetsVec_.empty() ){
               if( groomedJetsVec_.size() == oriJetsVec.size() ){
                  forJetMassLVec = groomedJetsVec_;
               }else{
                  std::cout<<"\nWARNING ...   groomedJetsVec_.size : "<<groomedJetsVec_.size()<<"  NOT equal input oriJetsVec.size : "<<oriJetsVec.size()<<std::endl;
                  std::cout<<"reverting back to oriJetsVec for top mass determination! Please double-check the inputs!"<<std::endl<<std::endl;
               }
            }

            for(unsigned int ij=0; ij<oriJetsVec.size(); ij++){
               TLorentzVector perTopjetLVec = forJetMassLVec[ij];
               if( perTopjetLVec.M() <= highTopjetMass_ && perTopjetLVec.M() >= lowTopjetMass_ ){
                  tmpTopjetIdx.push_back(ij);
               }else{
                  tmpRemainIdx.push_back(ij);
               }
            }

// In the perComb, the first one and only one is the Top jet!
            for(unsigned int iw=0; iw<tmpTopjetIdx.size(); iw++){
               vector<int> perComb, perRemain;
               perComb.push_back(tmpTopjetIdx[iw]);
               for(int ij=0; ij<(int)oriJetsVec.size(); ij++){
                  if( ij == tmpTopjetIdx[iw] ) continue;
                  perRemain.push_back(ij);
               }
               tmpFinalCombfatJets.push_back(perComb); tmpFinalRemaining.push_back(perRemain);
               vector<vector<int> > perSubStruc;
               tmpFinalCombJetSubStruc.push_back(perSubStruc);
            }
         }

         void onlyfatJetsCloseInACone(const vector<int> &indexVec, const vector<TLorentzVector> &oriJetsVec, const std::vector<double> &recoJetsBtagCSVS, vector<vector<int> > &tmpFinalCombfatJets, vector<vector<int> > &tmpFinalRemaining, vector<vector<vector<int> > > &tmpFinalCombJetSubStruc){

            tmpFinalCombfatJets.clear(); tmpFinalRemaining.clear(); tmpFinalCombJetSubStruc.clear();
         
            vector<vector<int> > tempCombfatJets; vector<vector<int> > tempRemaining; vector<vector<vector<int> > > tempCombJetSubStruc;
         
            prepareCombination(indexVec, tempCombfatJets, tempRemaining, tempCombJetSubStruc);

            unsigned int tmpCombSize = tempCombfatJets.size();
         
            for(unsigned int ic=0; ic<tmpCombSize; ic++){
               if( filterfatJetWithDRcone(oriJetsVec, tempCombfatJets[ic], simuCAdeltaR_) ){
                  tmpFinalCombfatJets.push_back(tempCombfatJets[ic]);
                  tmpFinalRemaining.push_back(tempRemaining[ic]);
                  tmpFinalCombJetSubStruc.push_back(tempCombJetSubStruc[ic]);
               }
            }
           
            if( doWjetfatJets_ ){ 
               vector<vector<int> > tempWjetCombfatJets; vector<vector<int> > tempWjetRemaining; vector<vector<vector<int> > > tempWjetCombJetSubStruc;
               makeWjetfatJets(oriJetsVec, recoJetsBtagCSVS, tempWjetCombfatJets, tempWjetRemaining, tempWjetCombJetSubStruc);
               for(unsigned int ic=0; ic<tempWjetCombfatJets.size(); ic++){
                  if( filterfatJetWithDRcone(oriJetsVec, tempWjetCombfatJets[ic], simuCAdeltaR_) ){
                     tmpFinalCombfatJets.push_back(tempWjetCombfatJets[ic]);
                     tmpFinalRemaining.push_back(tempWjetRemaining[ic]);
                     tmpFinalCombJetSubStruc.push_back(tempWjetCombJetSubStruc[ic]);
                  }
               }
            }

            if( doTopjetfatJets_ ){ 
               vector<vector<int> > tempTopjetCombfatJets; vector<vector<int> > tempTopjetRemaining; vector<vector<vector<int> > > tempTopjetCombJetSubStruc;
               makeTopjetfatJets(oriJetsVec, recoJetsBtagCSVS, tempTopjetCombfatJets, tempTopjetRemaining, tempTopjetCombJetSubStruc);
               for(unsigned int ic=0; ic<tempTopjetCombfatJets.size(); ic++){
                  if( filterfatJetWithDRcone(oriJetsVec, tempTopjetCombfatJets[ic], simuCAdeltaR_) ){
                     tmpFinalCombfatJets.push_back(tempTopjetCombfatJets[ic]);
                     tmpFinalRemaining.push_back(tempTopjetRemaining[ic]);
                     tmpFinalCombJetSubStruc.push_back(tempTopjetCombJetSubStruc[ic]);
                  }
               }
            }

            ptOrderedfatJets(oriJetsVec, tmpFinalCombfatJets, tmpFinalRemaining, tmpFinalCombJetSubStruc);
         }

         double calcMT2(const TLorentzVector &fatJet1LVec, const TLorentzVector &fatJet2LVec, const TLorentzVector &metLVec){

            // For this example we will use the "Basic_Mt2_332_Calculator" which is
            // the algorithm we recommend people use by default.
            // Mt2::Basic_Mt2_332_Calculator mt2Calculator;
            Mt2::ChengHanBisect_Mt2_332_Calculator mt2Calculator;
          
            // Could tell the MT2 calculating object to be verbose, and print out
            // debug messages while it is thinking ... but we won't:
            
            // mt2Calculator.setDebug(true);
            
            // The input parameters associated with the particle
            // (or collection of particles) associated with the
            // first "side" of the event: 
            const double massOfSystemA =  fatJet1LVec.M(); // GeV
            const double pxOfSystemA   =  fatJet1LVec.Px(); // GeV
            const double pyOfSystemA   =  fatJet1LVec.Py(); // GeV
            
            // The input parameters associated with the particle
            // (or collection of particles) associated with the
            // second "side" of the event:
            const double massOfSystemB =  fatJet2LVec.M(); // GeV
            const double pxOfSystemB   =  fatJet2LVec.Px(); // GeV
            const double pyOfSystemB   =  fatJet2LVec.Py(); // GeV
            
            // The missing transverse momentum:
            const double pxMiss        = metLVec.Px(); // GeV
            const double pyMiss        = metLVec.Py(); // GeV
            
            // The mass of the "inivisible" particle presumed to have
            // been produced at the end of the decay chain in each
            // "half" of the event:    
            const double invis_mass    = metLVec.M(); // GeV
            // Now put the inputs together into the input structures that the library wants.
          
            /*
                Note: in the next two lines (constructing "vis_A" and "vis_B"),
                the ORDER of the arguments to the constructor of
                Mt2::LorentzTransverseVector is very important.
                You need to be careful as, when the TwoVector comes
                first, the second arguments is taken to be a mass:
          
                LorentzTransverseVector(const TwoVector& momentum, double mass);
          
                but when the TwoVector comes second, the first arguemt is an ET=Sqrt(m^2+pt^2):
          
                LorentzTransverseVector(double Et, const TwoVector& momentum);
          
                You have been warned!
            */
          
            Mt2::LorentzTransverseVector  vis_A(Mt2::TwoVector(pxOfSystemA, pyOfSystemA), massOfSystemA);
            Mt2::LorentzTransverseVector  vis_B(Mt2::TwoVector(pxOfSystemB, pyOfSystemB), massOfSystemB);
            Mt2::TwoVector                pT_Miss(pxMiss, pyMiss);
          
            // Now that we have some visiable momenta and some missing transverse
            // momentum we can calculate MT2.
          
            const double mt2 = mt2Calculator.mt2_332(vis_A, vis_B, pT_Miss, invis_mass);
          
            return mt2;
         }

         double calcMT(const TLorentzVector &objLVec, const TLorentzVector &metLVec){
 
            const double objMass = objLVec.M(), objPt = objLVec.Pt(), objPx = objLVec.Px(), objPy = objLVec.Py();
            const double met = metLVec.Pt(), metphi = metLVec.Phi();

            double mt = sqrt( objMass*objMass + 2*( met*sqrt(objMass*objMass + objPt*objPt) -( met*cos(metphi)*objPx + met*sin(metphi)*objPy ) ) );

            return mt;
         }

         void prepareFindingBestTopCandidate(const std::vector<TLorentzVector> &oriJetsVec, const std::vector<double> &recoJetsBtagCSVS){

            vector<int> indexVec; for(size ij=0; ij<oriJetsVec.size(); ij++) indexVec.push_back(ij);

            onlyfatJetsCloseInACone(indexVec, oriJetsVec, recoJetsBtagCSVS, finalCombfatJets, finalRemaining, finalCombJetSubStruc);

            combSize = finalCombfatJets.size();

            for(size ij=0; ij<oriJetsVec.size(); ij++){
               if( recoJetsBtagCSVS[ij] > globalCachedCSVS_ && fabs(oriJetsVec[ij].Eta())<maxEtaForbJets_ ) cntnbJetsCSVS ++;
            }

            if( bVetoMethod_ == 0 ){
               if( cntnbJetsCSVS == 0 ){
                  int adjustedmaxJetIdx = -1;
                  double adjustedmaxCSVS = -1;
                  for(size ij=0; ij<oriJetsVec.size(); ij++){
                     if( fabs(oriJetsVec[ij].Eta())<maxEtaForbJets_ ){
                        if( adjustedmaxJetIdx == -1 ){ adjustedmaxCSVS = recoJetsBtagCSVS[ij]; adjustedmaxJetIdx = ij; }
                        else if( adjustedmaxCSVS < recoJetsBtagCSVS[ij] ){ adjustedmaxCSVS = recoJetsBtagCSVS[ij]; adjustedmaxJetIdx = ij; }
                     }
                  }
                  int adjustedsecJetIdx = -1; // second CSVS in order 
                  double adjustedsecCSVS = -1;
                  for(size ij=0; ij<oriJetsVec.size(); ij++){
                     if( fabs(oriJetsVec[ij].Eta())<maxEtaForbJets_ ){
                        if( recoJetsBtagCSVS[ij] == adjustedmaxCSVS ) continue;
                        if( adjustedsecJetIdx == -1 ){ adjustedsecCSVS = recoJetsBtagCSVS[ij]; adjustedsecJetIdx = ij; }
                        else if( adjustedsecCSVS < recoJetsBtagCSVS[ij] ){ adjustedsecCSVS = recoJetsBtagCSVS[ij]; adjustedsecJetIdx = ij; }
                     }
                  }
                  if( adjustedmaxJetIdx != -1 ){
                     CSVS_ = adjustedmaxCSVS - 1e10;
                     if( adjustedsecJetIdx != -1 ) CSVS_ = 0.5*(adjustedmaxCSVS + adjustedsecCSVS);
                  }
                  for(size ij=0; ij<oriJetsVec.size(); ij++){
                     if( recoJetsBtagCSVS[ij] > CSVS_ && fabs(oriJetsVec[ij].Eta())<maxEtaForbJets_ ) cntnbJetsCSVS ++;
                  }
               }else{
                   CSVS_ = globalCachedCSVS_;
               }
            }else if( bVetoMethod_ == 1 ){
               if( cntnbJetsCSVS == 0 ){
                  CSVS_ = minCSVS_disablebtag;
                  dobVetoCS_ = true;
                  for(size ij=0; ij<oriJetsVec.size(); ij++){
                     if( recoJetsBtagCSVS[ij] > CSVS_ && fabs(oriJetsVec[ij].Eta())<maxEtaForbJets_ ) cntnbJetsCSVS ++;
                  }
               }else{
                  CSVS_ = globalCachedCSVS_;
                  dobVetoCS_ = globalCacheddobVetoCS_;
               }
            }

            for(int ic=0; ic<combSize; ic++){
               TLorentzVector centralLVec = buildLVec(oriJetsVec, finalCombfatJets[ic]);
               double maxDR = 0.0;
               for(unsigned int is=0; is<finalCombfatJets[ic].size(); is++){
                  TLorentzVector perJetLVec = oriJetsVec[finalCombfatJets[ic][is]];
                  double perDR = perJetLVec.DeltaR(centralLVec);
                  if( maxDR < perDR ) maxDR = perDR;
               }
               finalCombMaxDR.push_back(maxDR);

               fatJetMassVec.push_back(buildLVec(oriJetsVec, finalCombfatJets[ic]).M());

               vector<double> perfatJetSubMassVec;
               calcSubStrucMass(oriJetsVec, finalCombJetSubStruc[ic], perfatJetSubMassVec);
               fatJetSubMassVec.push_back(perfatJetSubMassVec);
            }
         }

         void findBestTopCandidate(const std::vector<TLorentzVector> &oriJetsVec, const std::vector<double> &recoJetsBtagCSVS){

            double pickedMinChisq = -1;
            for(int ic=0; ic<combSize; ic++){
            
               double fatJetm123 = fatJetMassVec[ic];
               double fatJetm12 = -1,  fatJetm13 = -1, fatJetm23 = -1;
               for(unsigned int is=0; is<fatJetSubMassVec[ic].size(); is++){
                  if( is==0 ) fatJetm12 = fatJetSubMassVec[ic][is];
                  if( is==1 ) fatJetm13 = fatJetSubMassVec[ic][is];
                  if( is==2 ) fatJetm23 = fatJetSubMassVec[ic][is];
               }
               
         // Find a top fat jet passing at least one of the three criteria
               vector<int> fatJetPassStatusVec;
               int isTopJet = checkTopCriteria(finalCombfatJets[ic], oriJetsVec, recoJetsBtagCSVS, fatJetSubMassVec[ic], fatJetm123, fatJetPassStatusVec);
               if( doInvertTopCriteria_ ){ if( isTopJet ) isTopJet = 0; else isTopJet = 1; }
               finalCombfatJetsPassStatusVec.push_back(fatJetPassStatusVec);
               if( isTopJet ){
                  isTopEvent = true;
                  nTopJetCandCnt ++;
                  if( fatJetm123 > lowTopCut_ && fatJetm123 < highTopCut_ ){
                     topJetCand_deltaM_idx123Map[std::abs(fatJetm123-mTop_)] = finalCombfatJets[ic];
                  }
               }  

               int cntTopCandPassCSVS = 0;
               double bestmxy = -1;
               for(unsigned int it=0; it<finalCombfatJets[ic].size() && finalCombfatJets[ic].size() ==3; it++){
                  int idx = finalCombfatJets[ic][it];
                  if( recoJetsBtagCSVS[idx] > CSVS_ && fabs(oriJetsVec[idx].Eta())<maxEtaForbJets_ ){
                     cntTopCandPassCSVS++;
                     if( bestmxy == -1 ){
                        if( it==0 ) bestmxy = fatJetm23;
                        if( it==1 ) bestmxy = fatJetm13;
                        if( it==2 ) bestmxy = fatJetm12;
                     }else{
                        if( it==0 && fabs( fatJetm23 - mW_ ) < fabs( bestmxy - mW_ ) ) bestmxy = fatJetm23;
                        if( it==1 && fabs( fatJetm13 - mW_ ) < fabs( bestmxy - mW_ ) ) bestmxy = fatJetm13;
                        if( it==2 && fabs( fatJetm12 - mW_ ) < fabs( bestmxy - mW_ ) ) bestmxy = fatJetm12;
                     }
                  }
               }
               for(unsigned int it=0; it<finalCombfatJets[ic].size() && finalCombfatJets[ic].size() ==2; it++){
                  bestmxy = fatJetm12;
                  int idx = finalCombfatJets[ic][it];
                  if( recoJetsBtagCSVS[idx] > CSVS_ && fabs(oriJetsVec[idx].Eta())<maxEtaForbJets_ ) cntTopCandPassCSVS++;
               }
               for(unsigned int it=0; it<finalCombfatJets[ic].size() && finalCombfatJets[ic].size() ==1; it++){
                  int idx = finalCombfatJets[ic][it];
                  if( recoJetsBtagCSVS[idx] > CSVS_ && fabs(oriJetsVec[idx].Eta())<maxEtaForbJets_ ) cntTopCandPassCSVS++;
               }

               cntTopCandPassCSVSVec.push_back(cntTopCandPassCSVS);
               if( finalCombfatJets[ic].size() !=1 && bestmxy == -1 && cntTopCandPassCSVS !=0 ) std::cout<<"WARNING ... NO best W found when b appears ?!"<<"  INFO : finalCombfatJets[ic].size : "<<finalCombfatJets[ic].size()<<std::endl;
         
               if( cntTopCandPassCSVS == 0 && finalCombfatJets[ic].size() ==3 ){
                  for(unsigned int it=0; it<finalCombJetSubStruc[ic].size(); it++){
                     if( bestmxy == -1 ){
                        if( it==0 ) bestmxy = fatJetm23;
                        if( it==1 ) bestmxy = fatJetm13;
                        if( it==2 ) bestmxy = fatJetm12;
                     }else{
                        if( it==0 && fabs( fatJetm23 - mW_ ) < fabs( bestmxy - mW_ ) ) bestmxy = fatJetm23;
                        if( it==1 && fabs( fatJetm13 - mW_ ) < fabs( bestmxy - mW_ ) ) bestmxy = fatJetm13;
                        if( it==2 && fabs( fatJetm12 - mW_ ) < fabs( bestmxy - mW_ ) ) bestmxy = fatJetm12;
                     }
                  }
               }
         
               if( finalCombfatJets[ic].size() !=1 && bestmxy == -1 ) std::cout<<"WARNING ... NO best W found?!"<<std::endl;
         
               double chisq = (fatJetm123 - mTop_)*(fatJetm123 - mTop_)*(bestmxy - mW_)*(bestmxy - mW_);
               if( finalCombfatJets[ic].size() == 1 ) chisq = (fatJetm123 - mTop_)*(fatJetm123 - mTop_)*(fatJetm123 - mTop_)*(fatJetm123 - mTop_);
         
         // Find a tagged b-jet in the remaining jets corresponding to the top fat jet configuration
               int cntRemainingPassCSVS = 0;
               for(unsigned int ir=0; ir<finalRemaining[ic].size(); ir++){
                  int idx = finalRemaining[ic][ir];
                  if( recoJetsBtagCSVS[idx] > CSVS_ && fabs(oriJetsVec[idx].Eta())<maxEtaForbJets_ ) cntRemainingPassCSVS++;
               }
               cntRemainingPassCSVSVec.push_back(cntRemainingPassCSVS);
         
         // If we have at least 2 b jets, we require the fat jet must contain at least one.
         // Then also the remaining jets contain at least one.
               if( cntRemainingPassCSVS + cntTopCandPassCSVS != cntnbJetsCSVS ){
                  std::cout<<"WARNING ... cntnbJetsCSVS : "<<cntnbJetsCSVS<<"  !=   cntRemainingPassCSVS : "<<cntRemainingPassCSVS<<"  +  cntTopCandPassCSVS : "<<cntTopCandPassCSVS<<std::endl;
               }
               if( finalCombfatJets[ic].size() !=1 && cntnbJetsCSVS >=2 && cntTopCandPassCSVS == 0 ) continue;
         
         // This "isTopJet && cntRemainingPassCSVS" configuration is what we want
         // We can have multiple such combination in one event
               if( isTopJet && (cntRemainingPassCSVS || finalRemaining[ic].empty()) ){
                  nTopJetCandWithBtagCnt ++;
                  if( orderingOptArr_[0] == "chisq" ){
                     if( bestTopJetIdx == -1 ){
                        bestTopJetIdx = ic;
                        pickedMinChisq = chisq;
                     }else if( pickedMinChisq > chisq ){
                        bestTopJetIdx = ic;
                        pickedMinChisq = chisq;
                     }
                  }else if( orderingOptArr_[0] == "dr" ){
                     if( bestTopJetIdx == -1 ){
                         bestTopJetIdx = ic;
                     }else if( finalCombMaxDR[bestTopJetIdx] > finalCombMaxDR[ic] ){
                         bestTopJetIdx = ic;
                     }
                  }else if( orderingOptArr_[0] == "mass" ){
                     if( bestTopJetIdx == -1 ){
                        bestTopJetIdx = ic;
                     }else{
                        double pickedTopMass = fatJetMassVec[bestTopJetIdx];
         // Find the configuration of an event (with a <top fat jet, tagged b-jet> combination) with 
         // the best top mass of the top fat jet
                        if( fabs(pickedTopMass - mTop_) > fabs( fatJetm123 - mTop_ ) ){
                           bestTopJetIdx = ic;
                        }
                     }
                  }else if( orderingOptArr_[0] == "pt" ){
                     if( (int)ic<=maxIndexForOrderingArr_[0] ){
                        if( bestTopJetIdx == -1 ){
                           bestTopJetIdx = ic;
                        }
                     }
                  }else if( orderingOptArr_[0] == "hybrid" ){
                     if( (int)ic<=maxIndexForOrderingArr_[0] ){
                        if( bestTopJetIdx == -1 ){
                           bestTopJetIdx = ic;
                        }else{
                           double pickedTopMass = fatJetMassVec[bestTopJetIdx];
                           if( fabs(pickedTopMass - mTop_) > fabs( fatJetm123 - mTop_ ) ){
                              bestTopJetIdx = ic;
                           }
                        }
                     }
                  }
               }
            }

            if( doCombTopTagger_ ){
               std::vector<int> pickedTopIdxVec;
               topTaggerLowPt(oriJetsVec, recoJetsBtagCSVS, pickedTopIdxVec);
               TLorentzVector tmpTopLVec;
               if( bestTopJetIdx !=-1 ) tmpTopLVec = buildLVec(oriJetsVec, finalCombfatJets[bestTopJetIdx]);
               if( !pickedTopIdxVec.empty() ){
//                  TLorentzVector tmpPickedTopLVec = buildLVec(oriJetsVec, pickedTopIdxVec);
                  if( ( bestTopJetIdx !=-1 && tmpTopLVec.Pt() < lowTopPtToComb_) || bestTopJetIdx==-1 ){

                     std::vector<int> pickedRemainIdxVec;
                     for(unsigned int ij = 0; ij<oriJetsVec.size(); ij++){
                        bool foundIdx = false;
                        for(unsigned int ip=0; ip<pickedTopIdxVec.size(); ip++){
                           if( (int)ij == pickedTopIdxVec[ip] ) foundIdx = true;
                        }
                        if( foundIdx ) continue;
                        pickedRemainIdxVec.push_back(ij);
                     }

                     vector<vector<int> > pickedSubStruc;
                     buildSubStrucIndexComb(pickedTopIdxVec, pickedSubStruc);

                     finalCombfatJets.push_back(pickedTopIdxVec);
                     finalCombJetSubStruc.push_back(pickedSubStruc);
                     finalRemaining.push_back(pickedRemainIdxVec);

                     bestTopJetIdx = finalCombfatJets.size()-1;
                  }
               }
            }
         }

         void runOnlyTopTaggerPart(const std::vector<TLorentzVector> &oriJetsVec, const std::vector<double> &recoJetsBtagCSVS){

            setDefaultVars();

            double cachedCSVS = CSVS_;
            double cachedmaxEtaForbJets = maxEtaForbJets_;
            double cachedglobalCachedCSVS = globalCachedCSVS_;
            int cachedbVetoMethod = bVetoMethod_;
    
            CSVS_ = minCSVS_disablebtag; globalCachedCSVS_ = minCSVS_disablebtag; maxEtaForbJets_ = maxEta_disablebtag; bVetoMethod_ = 1;
            prepareFindingBestTopCandidate(oriJetsVec, recoJetsBtagCSVS);
            findBestTopCandidate(oriJetsVec, recoJetsBtagCSVS);
            fillingBestTopCandidateVars(oriJetsVec, recoJetsBtagCSVS);

            CSVS_ = cachedCSVS; globalCachedCSVS_ = cachedglobalCachedCSVS; maxEtaForbJets_ = cachedmaxEtaForbJets; bVetoMethod_ = cachedbVetoMethod;

         }

         void fillingBestTopCandidateVars(const std::vector<TLorentzVector> &oriJetsVec, const std::vector<double> &recoJetsBtagCSVS){

            if( bestTopJetIdx == -1 ) return;

            bestTopJetComb = finalCombfatJets[bestTopJetIdx];
            bestTopJetSubStruc = finalCombJetSubStruc[bestTopJetIdx];
                  
            remainTopJetComb = finalRemaining[bestTopJetIdx];
            remainJetNum = remainTopJetComb.size();

//      if( (int)bestTopJetComb.size() + remainJetNum != (int)oriJetsVec.size() ){ std::cout<<"WARNING ... bestTopJetComb.size : "<<bestTopJetComb.size()<<" + "<<"  remainJetNum : "<<remainJetNum<<"  NOT equal to oriJetsVec.size : "<<oriJetsVec.size()<<std::endl; }
               
            bestTopJetLVec = buildLVec(oriJetsVec, bestTopJetComb);

            bestTopJetMass = bestTopJetLVec.M();
               
            calcSubStrucMass(oriJetsVec, bestTopJetSubStruc, bestSubMassVec);

            for(unsigned int ir=0; ir<remainTopJetComb.size(); ir++){
               int idx = remainTopJetComb[ir];
               if( recoJetsBtagCSVS[idx] > CSVS_ && fabs(oriJetsVec[idx].Eta())<maxEtaForbJets_ ){
                  remainPassCSVS = true;
                  pickedbTaggedJetIdxVec.push_back(idx);

                  if( pickedbTaggedJetIdx == -1 ){
                     pickedbTaggedJetIdx = idx;
                     maxCSVS = recoJetsBtagCSVS[idx];
                  }else if( maxCSVS < recoJetsBtagCSVS[idx] && fabs(oriJetsVec[idx].Eta())<maxEtaForbJets_ ){
                     pickedbTaggedJetIdx = idx;
                     maxCSVS = recoJetsBtagCSVS[idx];
                  }
               }
            }

            for(unsigned int ib=0; ib<bestTopJetComb.size(); ib++){
               int idx = bestTopJetComb[ib];
               if( recoJetsBtagCSVS[idx] > CSVS_ && fabs(oriJetsVec[idx].Eta())<maxEtaForbJets_ ){
                  bestPassCSVS = true;
                  pickedbTaggedbestTopJetIdxVec.push_back(idx);
               }
            }

            for(unsigned int ib=0; ib<bestSubMassVec.size(); ib++){
               double perMjj = bestSubMassVec[ib];

               bool foundbJet = false;
               for(unsigned jb=0; jb<bestTopJetComb.size(); jb++){
                  bool isFound = false;
                  for(unsigned jr=0; jr<bestTopJetSubStruc[ib].size(); jr++){
                     if( bestTopJetSubStruc[ib][jr] == bestTopJetComb[jb] ) isFound = true;
                  }
                  if( !isFound ){
                     for(unsigned ipb=0; ipb<pickedbTaggedbestTopJetIdxVec.size(); ipb++){
                        if( bestTopJetComb[jb] == pickedbTaggedbestTopJetIdxVec[ipb] ) foundbJet = true;
                     }
                  }
               }
               if( !pickedbTaggedbestTopJetIdxVec.empty() && !foundbJet ) continue;

               if( bestCloseTomW == -1 ){
                  bestCloseTomW = perMjj;
                  bestCloseTomWLVec = buildLVec(oriJetsVec, bestTopJetSubStruc[ib]);
                  for(unsigned jb=0; jb<bestTopJetComb.size(); jb++){
                     TLorentzVector perbestbJetLVec = oriJetsVec[bestTopJetComb[jb]];
                     bool isFound = false;
                     for(unsigned jr=0; jr<bestTopJetSubStruc[ib].size(); jr++){
                        if( bestTopJetSubStruc[ib][jr] == bestTopJetComb[jb] ) isFound = true;
                     }
                     if( !isFound ) bestbJetLVec = perbestbJetLVec;
                  }
               }else if( fabs( bestCloseTomW - mW_ ) > fabs( perMjj - mW_ ) ){
                  bestCloseTomW = perMjj;
                  bestCloseTomWLVec = buildLVec(oriJetsVec, bestTopJetSubStruc[ib]);
                  for(unsigned jb=0; jb<bestTopJetComb.size(); jb++){
                     TLorentzVector perbestbJetLVec = oriJetsVec[bestTopJetComb[jb]];
                     bool isFound = false;
                     for(unsigned jr=0; jr<bestTopJetSubStruc[ib].size(); jr++){
                        if( bestTopJetSubStruc[ib][jr] == bestTopJetComb[jb] ) isFound = true;
                     }
                     if( !isFound ) bestbJetLVec = perbestbJetLVec;
                  }
               }
            }

            if( doCombTopTagger_ ){
               bestbJetLVec = oriJetsVec[bestTopJetComb.back()];
               bestCloseTomWLVec = buildLVec(oriJetsVec, bestTopJetSubStruc.front());
               bestCloseTomW = bestCloseTomWLVec.M();
            }
         }

         void prepareFindingRemainingTopCandidate(const std::vector<TLorentzVector> &oriJetsVec, const std::vector<double> &recoJetsBtagCSVS){
            if( !remainPassCSVS ) return;

            // Find a good top candidate in the remaining jets
            // Prepare all possible combination in the remaining jets
            prepareCombination(remainTopJetComb, finalRemainingCombfatJets, finalRemaining2, finalRemainingCombJetSubStruc);

            ptOrderedfatJets(oriJetsVec, finalRemainingCombfatJets, finalRemaining2, finalRemainingCombJetSubStruc);

            for(unsigned int ir=0; ir<finalRemainingCombfatJets.size(); ir++){
               TLorentzVector centralLVec = buildLVec(oriJetsVec, finalRemainingCombfatJets[ir]);
               double maxDR = 0.0;
               for(unsigned int is=0; is<finalRemainingCombfatJets[ir].size(); is++){
                  TLorentzVector perJetLVec = oriJetsVec[finalRemainingCombfatJets[ir][is]];
                  double perDR = perJetLVec.DeltaR(centralLVec);
                  if( maxDR < perDR ) maxDR = perDR;
               }
               finalRemainingCombMaxDR.push_back(maxDR);
            }
         }

         void findRemainingTopCandidate(const std::vector<TLorentzVector> &oriJetsVec, const std::vector<double> &recoJetsBtagCSVS){

         // Find the best top candidate in the fat jets combindation from the remaining jets
            double pickedRemainingMinChisq = -1;
            for(unsigned int ir=0; ir<finalRemainingCombfatJets.size(); ir++){

               double tmpTopMass = buildLVec(oriJetsVec, finalRemainingCombfatJets[ir]).M();

               if( !filterfatJetWithDRcone(oriJetsVec, finalRemainingCombfatJets[ir], simuCALargerdeltaR_) ) continue;

         // Must have a b-tagged jet in the triplet
         // XXX: Only criteria is to pick the one closest to top jet mass
               int cachedcntbTaggedIndex = cntbTaggedIndex;
               for(unsigned int ipb=0; ipb<pickedbTaggedJetIdxVec.size(); ipb++){
                  int tmpPickedbTaggedJetIdx = pickedbTaggedJetIdxVec[ipb];
                  vii it = find(finalRemainingCombfatJets[ir].begin(), finalRemainingCombfatJets[ir].end(), tmpPickedbTaggedJetIdx);
                  if( it != finalRemainingCombfatJets[ir].end() ){
         // Ensure that the index only added once for multiple b tagged cases
                     if( cachedcntbTaggedIndex == cntbTaggedIndex ) cntbTaggedIndex++;
         // Prepare for chisq method
                     unsigned int bJetIdxInRemainingCombfatJets = std::distance(finalRemainingCombfatJets[ir].begin(), it);
                     TLorentzVector tempRemainingmxyLVec;
                     if( bJetIdxInRemainingCombfatJets == 0 ){
                        tempRemainingmxyLVec = buildLVec(oriJetsVec, finalRemainingCombJetSubStruc[ir][2]);
                     }else if( bJetIdxInRemainingCombfatJets == 1 ){
                        tempRemainingmxyLVec = buildLVec(oriJetsVec, finalRemainingCombJetSubStruc[ir][1]);
                     }else if( bJetIdxInRemainingCombfatJets == 2 ){
                        tempRemainingmxyLVec = buildLVec(oriJetsVec, finalRemainingCombJetSubStruc[ir][0]);
                     }else{
                        std::cout<<"ERROR ...  bJetIdxInRemainingCombfatJets : "<<bJetIdxInRemainingCombfatJets<<std::endl;
                     }
                     double tmpWMass = tempRemainingmxyLVec.M();
                     double chisq = (tmpTopMass - mTop_)*(tmpTopMass - mTop_)*(tmpWMass - mW_)*(tmpWMass - mW_);
                     if( orderingOptArr_[1] == "chisq" ){
                        if( pickedRemainingCombfatJetIdx == -1 ){
                           pickedRemainingCombfatJetIdx = ir;
                           pickedRemainingCombfatJetMass = tmpTopMass;
                           pickedRemainingCombfatJetbJetIdx = tmpPickedbTaggedJetIdx;
                           pickedRemainingMinChisq = chisq;
                        }else if( pickedRemainingMinChisq > chisq ){
                           pickedRemainingCombfatJetIdx = ir;
                           pickedRemainingCombfatJetMass = tmpTopMass;
                           pickedRemainingCombfatJetbJetIdx = tmpPickedbTaggedJetIdx;
                           pickedRemainingMinChisq = chisq;
                        }
                     }else if( orderingOptArr_[1] == "dr" ){
                        if( pickedRemainingCombfatJetIdx == -1 ){
                           pickedRemainingCombfatJetIdx = ir;
                           pickedRemainingCombfatJetMass = tmpTopMass;
                           pickedRemainingCombfatJetbJetIdx = tmpPickedbTaggedJetIdx;
                        }else if( finalRemainingCombMaxDR[pickedRemainingCombfatJetIdx] > finalRemainingCombMaxDR[ir] ){
                           pickedRemainingCombfatJetIdx = ir;
                           pickedRemainingCombfatJetMass = tmpTopMass;
                           pickedRemainingCombfatJetbJetIdx = tmpPickedbTaggedJetIdx;
                        }
                     }else if( orderingOptArr_[1] == "mass" ){
                        if( pickedRemainingCombfatJetIdx == -1 ){
                           pickedRemainingCombfatJetIdx = ir;
                           pickedRemainingCombfatJetMass = tmpTopMass;
                           pickedRemainingCombfatJetbJetIdx = tmpPickedbTaggedJetIdx;
                        }else if( fabs(pickedRemainingCombfatJetMass - mTop_ ) > fabs(tmpTopMass - mTop_) ){
                           pickedRemainingCombfatJetIdx = ir;
                           pickedRemainingCombfatJetMass = tmpTopMass;
                           pickedRemainingCombfatJetbJetIdx = tmpPickedbTaggedJetIdx;
                        }
                     }else if( orderingOptArr_[1] == "pt" ){
                        if( cntbTaggedIndex <=maxIndexForOrderingArr_[1] ){
                           if( pickedRemainingCombfatJetIdx == -1 ){
                              pickedRemainingCombfatJetIdx = ir;
                              pickedRemainingCombfatJetMass = tmpTopMass;
                              pickedRemainingCombfatJetbJetIdx = tmpPickedbTaggedJetIdx;
                           }
                        }
                     }else if( orderingOptArr_[1] == "hybrid" ){
                        if( cntbTaggedIndex <=maxIndexForOrderingArr_[1] ){
                           if( pickedRemainingCombfatJetIdx == -1 ){
                              pickedRemainingCombfatJetIdx = ir;
                              pickedRemainingCombfatJetMass = tmpTopMass;
                              pickedRemainingCombfatJetbJetIdx = tmpPickedbTaggedJetIdx;
                           }else if( fabs(pickedRemainingCombfatJetMass - mTop_ ) > fabs(tmpTopMass - mTop_) ){
                              pickedRemainingCombfatJetIdx = ir;
                              pickedRemainingCombfatJetMass = tmpTopMass;
                              pickedRemainingCombfatJetbJetIdx = tmpPickedbTaggedJetIdx;
                           }
                        }
                     }
                  }
               }
            }
         }

         void fillingRemainingTopCandidate(const std::vector<TLorentzVector> &oriJetsVec, const std::vector<double> &recoJetsBtagCSVS){
            if( pickedRemainingCombfatJetIdx == -1 ) return;

            pickedRemainingCombfatJet = finalRemainingCombfatJets[pickedRemainingCombfatJetIdx];
            pickedRemainingCombJetSubStruc = finalRemainingCombJetSubStruc[pickedRemainingCombfatJetIdx];

            remainingTopJetLVec = buildLVec(oriJetsVec, pickedRemainingCombfatJet);

            pickedRemainingfatJetMass = remainingTopJetLVec.M();

            calcSubStrucMass(oriJetsVec, pickedRemainingCombJetSubStruc, pickedRemainingSubMassVec);

            for(unsigned int ip = 0; ip<pickedRemainingSubMassVec.size(); ip++){
               double perMjj = pickedRemainingSubMassVec[ip];
               if( pickedRemainingCloseTomW == -1 ){
                  pickedRemainingCloseTomW = perMjj;
               }else if( fabs(pickedRemainingCloseTomW - mW_) > fabs(perMjj - mW_) ){
                  pickedRemainingCloseTomW = perMjj;
               }
            }
         }

         void tunningRemainingJetSystem(const std::vector<TLorentzVector> &oriJetsVec, const std::vector<double> &recoJetsBtagCSVS, const TLorentzVector &metLVec){
            if( pickedRemainingCombfatJetIdx == -1 && remainJetNum >=3 ) return;

            if( remainJetNum >=3 ){
            // Find the mxy pair that does not contain a b jet --> most likely the W candidate
               for( unsigned int isc=0; isc<pickedRemainingCombJetSubStruc.size(); isc++){
                  vii it = find(pickedRemainingCombJetSubStruc[isc].begin(), pickedRemainingCombJetSubStruc[isc].end(), pickedRemainingCombfatJetbJetIdx);
                  if( it == pickedRemainingCombJetSubStruc[isc].end() ){
                     pickedRemainingmxyPair = pickedRemainingCombJetSubStruc[isc];
                  }
               }
               pickedRemainingmxy = buildLVec(oriJetsVec, pickedRemainingmxyPair).M();
               pickedRemainingbJetLVec = oriJetsVec[pickedRemainingCombfatJetbJetIdx];
            }
            if( remainJetNum == 2 ){
               int tmpclosebJetIdx = -1;
               double tmpclosebJetDphi = -1; //tmpPseudomxyIdx = -1;
               double metphi = metLVec.Phi();
// Currently closest b jet to met criteria since it helps to reduce background
               for(unsigned int ipb=0; ipb<pickedbTaggedJetIdxVec.size(); ipb++){
                  if( tmpclosebJetIdx == -1 ){
                     tmpclosebJetIdx = pickedbTaggedJetIdxVec[ipb];
                     tmpclosebJetDphi = fabs(TVector2::Phi_mpi_pi( oriJetsVec[pickedbTaggedJetIdxVec[ipb]].Phi() - metphi));
                  }else if( tmpclosebJetDphi > fabs(TVector2::Phi_mpi_pi( oriJetsVec[pickedbTaggedJetIdxVec[ipb]].Phi() - metphi)) ){
                     tmpclosebJetIdx = pickedbTaggedJetIdxVec[ipb];
                     tmpclosebJetDphi = fabs(TVector2::Phi_mpi_pi( oriJetsVec[pickedbTaggedJetIdxVec[ipb]].Phi() - metphi));
                  }
               }
               for(unsigned int ir=0; ir<remainTopJetComb.size(); ir++){
//                  int idx = remainTopJetComb[ir];
//                  if( idx != tmpclosebJetIdx ) tmpPseudomxyIdx = idx;
               }
// No remaining mxy
               pickedRemainingmxy = -1;
// This is the picked b jet
               if( tmpclosebJetIdx != -1 ) pickedRemainingbJetLVec = oriJetsVec[tmpclosebJetIdx];
// This pickedRemainingCombfatJetbJetIdx has to be changed to tmpclosebJetIdx
// in order for the following procedure.
               pickedRemainingCombfatJetbJetIdx = tmpclosebJetIdx;
            }
            if( remainJetNum == 1 ){
               pickedRemainingmxy = -1;
               pickedRemainingCombfatJetbJetIdx = remainTopJetComb.front();
               pickedRemainingbJetLVec = oriJetsVec[pickedRemainingCombfatJetbJetIdx];
            }

            // Find the other one jet that is closest to the b jet --> most likely the W->tau->had
            for(unsigned int ir=0; ir<remainTopJetComb.size(); ir++){
               int idx = remainTopJetComb[ir];
               if( pickedRemainingCombfatJetbJetIdx == idx ) continue;
               TLorentzVector tryJetLVec = oriJetsVec[idx];
               TLorentzVector combJetLVec = tryJetLVec + pickedRemainingbJetLVec;
            // b + another jet could NOT have mass larger than top quark mass
               if( combJetLVec.M() > mTop_ ) continue;
               double deltaR = pickedRemainingbJetLVec.DeltaR(tryJetLVec);
               if( pickedClosestJetTobIdx == -1 ){
                  pickedClosestJetTobIdx = idx;
                  pickedClosestJetTobDeltaR = deltaR;
               }else if( pickedClosestJetTobDeltaR > deltaR ){
                  pickedClosestJetTobIdx = idx;
                  pickedClosestJetTobDeltaR = deltaR;
               }
            }

            // If deltaR is too large, the other jet is NOT associated with the b
            if( pickedClosestJetTobDeltaR > defaultJetCone_ ) pickedClosestJetTobIdx = -1;
            if( pickedClosestJetTobIdx != -1 ) pickedRemainingbJetPlusAJetLVec  = pickedRemainingbJetLVec + oriJetsVec[pickedClosestJetTobIdx];
         }

         void prepareCutVariables(const std::vector<TLorentzVector> &oriJetsVec, const std::vector<double> &recoJetsBtagCSVS, const TLorentzVector &metLVec){
            if( bestTopJetIdx == -1 || (pickedRemainingCombfatJetIdx == -1 && remainJetNum >=3) ) return;

            double metphi = metLVec.Phi();

            mTbestTopJet = calcMT(bestTopJetLVec, metLVec);

            if( !bestSubMassVec.empty() ) mTbestWJet = calcMT(bestCloseTomWLVec, metLVec);

            if( !bestSubMassVec.empty() ) mTbestbJet = calcMT(bestbJetLVec, metLVec);

//            mTremainingTopJet = calcMT(remainingTopJetLVec, metLVec);

            closemT = mTbestTopJet;
            if( fabs(TVector2::Phi_mpi_pi(bestTopJetLVec.Phi() - metphi)) > fabs(TVector2::Phi_mpi_pi(remainingTopJetLVec.Phi() - metphi )) ) closemT = mTremainingTopJet;

            for(unsigned int ipb=0; ipb<pickedbTaggedJetIdxVec.size(); ipb++){
               if( closebJetIdx == -1 ){
                  closebJetIdx = pickedbTaggedJetIdxVec[ipb];
                  closebJetDphi = fabs(TVector2::Phi_mpi_pi( oriJetsVec[pickedbTaggedJetIdxVec[ipb]].Phi() - metphi));
               }else if( closebJetDphi > fabs(TVector2::Phi_mpi_pi( oriJetsVec[pickedbTaggedJetIdxVec[ipb]].Phi() - metphi)) ){
                  closebJetIdx = pickedbTaggedJetIdxVec[ipb];
                  closebJetDphi = fabs(TVector2::Phi_mpi_pi( oriJetsVec[pickedbTaggedJetIdxVec[ipb]].Phi() - metphi));
               }
            }

            closebJetLVec = oriJetsVec[closebJetIdx];

            mTbJet = calcMT(closebJetLVec, metLVec); 

            if( pickedClosestJetTobIdx != -1 && pickedRemainingCombfatJetbJetIdx == closebJetIdx ){
               mTbJet = calcMT(pickedRemainingbJetPlusAJetLVec, metLVec);
            }

// Assume only one b jet in the R-system, so the closebJet is 
// always the same as the b jet picked from the triplet in the R-system
            if( dobVetoCS_ ){ 
               mTbJet = calcMT(pickedRemainingbJetLVec, metLVec);
               if( pickedClosestJetTobIdx != -1 ) mTbJet = calcMT(pickedRemainingbJetPlusAJetLVec, metLVec);
            }

            if( pickedRemainingmxy < lowWCut_ || pickedRemainingmxy > highWCut_ ){
            // This is NOT a good W candidate & there is a jet associated with the b jet --> possible b+tau(had) candidate
               if( pickedClosestJetTobIdx != -1 ){
                  MT2 = calcMT2(bestTopJetLVec, pickedRemainingbJetPlusAJetLVec, metLVec);
                  mTremainingTopJet = calcMT(pickedRemainingbJetPlusAJetLVec, metLVec);
               }else{
            // This is NOT a good W candidate & no other jet associated with the b jet --> use only the b jet
                  MT2 = calcMT2(bestTopJetLVec, pickedRemainingbJetLVec, metLVec);
                  mTremainingTopJet = calcMT(pickedRemainingbJetLVec, metLVec);
               }
            }else{
            // We have a good W candidate --> use the remainingTopJetLVec
               MT2 = calcMT2(bestTopJetLVec, remainingTopJetLVec, metLVec);
               mTremainingTopJet = calcMT(remainingTopJetLVec, metLVec);
            }
         }

         bool applyCuts(){

            bool pass = true;

// Must have a fat top jet
            if( !taggingMode_ && bestTopJetIdx == -1 ) pass = false;

// Some mass cuts on the fat top jet
            if( !taggingMode_ && !(bestTopJetMass > lowTopCut_ && bestTopJetMass < highTopCut_) ) pass = false;

// Must have a jet b-tagged!
            if( !taggingMode_ && !remainPassCSVS ) pass = false;

// Must have another fat jet in the remaining part of the events
// Well, this is definitely true for a "t + tbar" event
            if( !taggingMode_ && (pickedRemainingCombfatJetIdx == -1 && remainJetNum >=3) ) pass = false;
  
            if( !taggingMode_ && doMTMT2cuts_ && !(MT2 > MT2cut_ && (mTbJet + 0.5*mTbestTopJet) > mTbcut_) ) pass = false; 

            return pass;
         }

         int findnTopCands(const std::vector<TLorentzVector> &oriJetsVec){
            nTopCandSortedCnt =0;

            allIdxCacheVec.clear(); pickedTopCandSortedVec.clear();

            if( bestTopJetIdx != -1 ){
               for(unsigned int it=0; it< bestTopJetComb.size(); it++){
                  allIdxCacheVec.push_back(bestTopJetComb.at(it));
               }
               nTopCandSortedCnt++;
               pickedTopCandSortedVec.push_back(bestTopJetIdx);
            }

            double minDeltaM = -1;
//            bool foundThePickedTop = false;
            std::map<double, vector<int> >::iterator mapIter;
            for(mapIter = topJetCand_deltaM_idx123Map.begin(); mapIter != topJetCand_deltaM_idx123Map.end(); mapIter++){

               if( minDeltaM != -1 && minDeltaM >= mapIter->first ){ std::cout<<"WARNING ... Type3TopTagger ... map not sorted correctly as what I want?!"<<std::endl; }
               minDeltaM = mapIter->first;

//               if( mapIter->second == bestTopJetComb ) foundThePickedTop = true;

               bool isFound = false;
               for(unsigned int ii=0; ii<mapIter->second.size(); ii++){
                  if( std::find(allIdxCacheVec.begin(), allIdxCacheVec.end(), mapIter->second.at(ii)) != allIdxCacheVec.end() ){
                     isFound = true;
                  }
               }
               if( !isFound ){
                  for(unsigned int ii=0; ii<mapIter->second.size(); ii++) allIdxCacheVec.push_back(mapIter->second.at(ii));
                  nTopCandSortedCnt ++;
                  int pickedCombIdx = -1;
                  for(int ic=0; ic<combSize; ic++){ if( finalCombfatJets[ic] == mapIter->second ) pickedCombIdx = ic; }
                  if( pickedCombIdx == -1 ){ std::cout<<"WARNING ... Type3TopTagger ... mis-matching between topJetCand_deltaM_idx123Map and finalCombfatJets?!"<<std::endl; }
                  if( std::find(pickedTopCandSortedVec.begin(), pickedTopCandSortedVec.end(), pickedCombIdx) != pickedTopCandSortedVec.end() ) std::cout<<"WARNING ... Type3TopTagger ... double counting top candidates?!"<<std::endl;
                  else pickedTopCandSortedVec.push_back( pickedCombIdx );
               }
            }
            return nTopCandSortedCnt;
         }

         bool processEvent(const std::vector<TLorentzVector> &oriJetsVec, const std::vector<double> &recoJetsBtagCSVS, const TLorentzVector &metLVec){

            int noriJets = oriJetsVec.size();

// Reset all variables to their default values
// before any further processing including nJetsSel verification!
            setDefaultVars();

            bool pass = true;

            if( noriJets < nJetsSel_ ) pass = false;
 
            if( noriJets >= nJetsSel_ ){

               prepareFindingBestTopCandidate(oriJetsVec, recoJetsBtagCSVS);
               findBestTopCandidate(oriJetsVec, recoJetsBtagCSVS);
               fillingBestTopCandidateVars(oriJetsVec, recoJetsBtagCSVS);

// For Di-Top cases
// XXX: Make sure the findDiTopCandidates function does NOT interfere with the major/main topTagger part, i.e., the "top + b" cases.
//      --> No override of any global variables related to the main tagger results
//      --> No override of the pass decision
               findDiTopCandidates(oriJetsVec, recoJetsBtagCSVS);

// The number 6 is because we need 3 jets for each triplet
               if( noriJets >= 6 ){
                  prepareFindingRemainingTopCandidate(oriJetsVec, recoJetsBtagCSVS);
                  findRemainingTopCandidate(oriJetsVec, recoJetsBtagCSVS);
                  fillingRemainingTopCandidate(oriJetsVec, recoJetsBtagCSVS);
               }

               tunningRemainingJetSystem(oriJetsVec, recoJetsBtagCSVS, metLVec);

               prepareCutVariables(oriJetsVec, recoJetsBtagCSVS, metLVec);

               pass = applyCuts();

               findnTopCands(oriJetsVec);

            }else{
               pass = false;
            }

            return pass;

         }

         void resolveOverlappingJets(const std::vector<TLorentzVector> &oriJetsVec, const std::vector<double> &recoJetsBtagCSVS, const std::vector<TLorentzVector> &hepTaggerSubJetsVec, std::vector<int> &tmpremainingJetsVec, std::vector<double> &tmpremainingJetsBtagCSVS, std::vector<double> &hepTaggerSubJetsBtagCSVS){

            tmpremainingJetsVec.clear(); tmpremainingJetsBtagCSVS.clear(); hepTaggerSubJetsBtagCSVS.clear();
            unsigned int sizeSubJets = hepTaggerSubJetsVec.size();
            hepTaggerSubJetsBtagCSVS.resize(sizeSubJets, -1);
            for(unsigned int ij=0; ij<oriJetsVec.size(); ij++){
               TLorentzVector peroriJet = oriJetsVec[ij];
               double perBtagCSVS = recoJetsBtagCSVS[ij];
               vector<int> matchedIdxVec;
               for(unsigned int ih=0; ih<sizeSubJets; ih++){
                  TLorentzVector persubJet = hepTaggerSubJetsVec[ih];
                  double deltaR = peroriJet.DeltaR(persubJet);
                  if( deltaR < maxDRjetMatch_ ) matchedIdxVec.push_back(ih);
               }
               if( matchedIdxVec.empty() ){
                  tmpremainingJetsVec.push_back(ij);
                  tmpremainingJetsBtagCSVS.push_back(perBtagCSVS);
               }else{
                  if( matchedIdxVec.size() ==1 ){
                     hepTaggerSubJetsBtagCSVS[matchedIdxVec[0]] = perBtagCSVS;
                  }
               }
            }
         }

         void prepareANDfindBestTopCandidate(const std::vector<TLorentzVector> &oriJetsVec, const std::vector<double> &recoJetsBtagCSVS, const std::vector<std::vector<TLorentzVector> > &hepTaggerJetsVec, std::vector<TLorentzVector> &tmpModiforiJetsVec, std::vector<double> &tmpModifrecoJetsBtagCSVS){

            for(size ij=0; ij<oriJetsVec.size(); ij++){
               if( recoJetsBtagCSVS[ij] > CSVS_ && fabs(oriJetsVec[ij].Eta())<maxEtaForbJets_ ) cntnbJetsCSVS ++;
            }

            tmpModiforiJetsVec.clear(); tmpModifrecoJetsBtagCSVS.clear();

            std::vector<int> tmpremainingJetsVec;
            std::vector<double> tmpremainingJetsBtagCSVS, hepTaggerSubJetsBtagCSVS;

            combSize = hepTaggerJetsVec.size();
            double pickedMinChisq = -1;
            for(int ic=0; ic<combSize; ic++){
            
               tmpModiforiJetsVec.clear(); tmpModifrecoJetsBtagCSVS.clear(); 
 
               std::vector<TLorentzVector> hepTaggerSubJetsVec = hepTaggerJetsVec[ic];

               resolveOverlappingJets(oriJetsVec, recoJetsBtagCSVS, hepTaggerSubJetsVec, tmpremainingJetsVec, tmpremainingJetsBtagCSVS, hepTaggerSubJetsBtagCSVS);

               std::vector<int> perfinalCombfatJets;
               for(unsigned int ih=0; ih<hepTaggerSubJetsVec.size(); ih++){
                  tmpModiforiJetsVec.push_back( hepTaggerSubJetsVec[ih] );
                  tmpModifrecoJetsBtagCSVS.push_back( hepTaggerSubJetsBtagCSVS[ih] );
                  perfinalCombfatJets.push_back(ih);
               }
               std::vector<std::vector<int> > perfinalCombJetSubStruc(3);
               perfinalCombJetSubStruc[0].push_back(0); perfinalCombJetSubStruc[0].push_back(1);
               perfinalCombJetSubStruc[1].push_back(0); perfinalCombJetSubStruc[1].push_back(2);
               perfinalCombJetSubStruc[2].push_back(1); perfinalCombJetSubStruc[2].push_back(2);

               finalCombfatJets.push_back(perfinalCombfatJets);
               finalCombJetSubStruc.push_back(perfinalCombJetSubStruc);

               std::vector<int> perfinalRemaining;
               for(unsigned int io=0; io<tmpremainingJetsVec.size(); io++){
                  tmpModiforiJetsVec.push_back( oriJetsVec[tmpremainingJetsVec[io]] );
                  tmpModifrecoJetsBtagCSVS.push_back( tmpremainingJetsBtagCSVS[io] );
                  perfinalRemaining.push_back( hepTaggerSubJetsVec.size() + io );
               }
               finalRemaining.push_back(perfinalRemaining);

               TLorentzVector combLVec = buildLVec(tmpModiforiJetsVec, finalCombfatJets[ic]);
               double maxDR = 0.0;
               for(unsigned int is=0; is<finalCombfatJets[ic].size(); is++){
                  TLorentzVector perJetLVec = tmpModiforiJetsVec[finalCombfatJets[ic][is]];
                  double perDR = perJetLVec.DeltaR(combLVec);
                  if( maxDR < perDR ) maxDR = perDR;
               }
               finalCombMaxDR.push_back(maxDR);

               std::vector<double> perfatJetSubMassVec;
                
               double fatJetm123 = combLVec.M();
               double fatJetm12 = buildLVec(tmpModiforiJetsVec, finalCombJetSubStruc[ic][0]).M();
               double fatJetm13 = buildLVec(tmpModiforiJetsVec, finalCombJetSubStruc[ic][1]).M();
               double fatJetm23 = buildLVec(tmpModiforiJetsVec, finalCombJetSubStruc[ic][2]).M();

               fatJetMassVec.push_back(fatJetm123);

               perfatJetSubMassVec.push_back(fatJetm12); perfatJetSubMassVec.push_back(fatJetm13); perfatJetSubMassVec.push_back(fatJetm23);
               fatJetSubMassVec.push_back(perfatJetSubMassVec);
               
         // Find a top fat jet passing at least one of the three criteria
               vector<int> fatJetPassStatusVec;
               int isTopJet = checkTopCriteria(finalCombfatJets[ic], oriJetsVec, recoJetsBtagCSVS, fatJetSubMassVec[ic], fatJetm123, fatJetPassStatusVec);
               if( doInvertTopCriteria_ ){ if( isTopJet ) isTopJet = 0; else isTopJet = 1; }
               finalCombfatJetsPassStatusVec.push_back(fatJetPassStatusVec);
               if( isTopJet ){
                  isTopEvent = true;
                  nTopJetCandCnt ++;
               }

               int cntTopCandPassCSVS = 0;
               double bestmxy = -1;
               for(unsigned int it=0; it<finalCombfatJets[ic].size(); it++){
                  int idx = finalCombfatJets[ic][it];
                  if( tmpModifrecoJetsBtagCSVS[idx] > CSVS_ && fabs(tmpModiforiJetsVec[idx].Eta())<maxEtaForbJets_ ){
                     cntTopCandPassCSVS++;
                     if( bestmxy == -1 ){
                        if( it==0 ) bestmxy = fatJetm23;
                        if( it==1 ) bestmxy = fatJetm13;
                        if( it==2 ) bestmxy = fatJetm12;
                     }else{
                        if( it==0 && fabs( fatJetm23 - mW_ ) < fabs( bestmxy - mW_ ) ) bestmxy = fatJetm23;
                        if( it==1 && fabs( fatJetm13 - mW_ ) < fabs( bestmxy - mW_ ) ) bestmxy = fatJetm13;
                        if( it==2 && fabs( fatJetm12 - mW_ ) < fabs( bestmxy - mW_ ) ) bestmxy = fatJetm12;
                     }
                  }
               }
               cntTopCandPassCSVSVec.push_back(cntTopCandPassCSVS);
               if( bestmxy == -1 && cntTopCandPassCSVS !=0 ) std::cout<<"WARNING ... NO best W found when b appears ?!"<<std::endl;
         
               if( cntTopCandPassCSVS == 0 ){
                  for(unsigned int it=0; it<finalCombJetSubStruc[ic].size(); it++){
                     if( bestmxy == -1 ){
                        if( it==0 ) bestmxy = fatJetm23;
                        if( it==1 ) bestmxy = fatJetm13;
                        if( it==2 ) bestmxy = fatJetm12;
                     }else{
                        if( it==0 && fabs( fatJetm23 - mW_ ) < fabs( bestmxy - mW_ ) ) bestmxy = fatJetm23;
                        if( it==1 && fabs( fatJetm13 - mW_ ) < fabs( bestmxy - mW_ ) ) bestmxy = fatJetm13;
                        if( it==2 && fabs( fatJetm12 - mW_ ) < fabs( bestmxy - mW_ ) ) bestmxy = fatJetm12;
                     }
                  }
               }
         
               if( bestmxy == -1 ) std::cout<<"WARNING ... NO best W found?!"<<std::endl;
         
               double chisq = (fatJetm123 - mTop_)*(fatJetm123 - mTop_)*(bestmxy - mW_)*(bestmxy - mW_);
         
         // Find a tagged b-jet in the remaining jets corresponding to the top fat jet configuration
               int cntRemainingPassCSVS = 0;
               for(unsigned int ir=0; ir<finalRemaining[ic].size(); ir++){
                  int idx = finalRemaining[ic][ir];
                  if( tmpModifrecoJetsBtagCSVS[idx] > CSVS_ && fabs(tmpModiforiJetsVec[idx].Eta())<maxEtaForbJets_ ) cntRemainingPassCSVS++;
               }
               cntRemainingPassCSVSVec.push_back(cntRemainingPassCSVS);
         
         // If we have at least 2 b jets, we require the fat jet must contain at least one.
         // Then also the remaining jets contain at least one.
               if( cntnbJetsCSVS >=2 && cntRemainingPassCSVS == cntnbJetsCSVS ) continue;
         
         // This "isTopJet && cntRemainingPassCSVS" configuration is what we want
         // We can have multiple such combination in one event
               if( isTopJet && (cntRemainingPassCSVS || finalRemaining[ic].empty()) ){
                  nTopJetCandWithBtagCnt ++;
                  if( orderingOptArr_[0] == "chisq" ){
                     if( bestTopJetIdx == -1 ){
                        bestTopJetIdx = ic;
                        pickedMinChisq = chisq;
                     }else if( pickedMinChisq > chisq ){
                        bestTopJetIdx = ic;
                        pickedMinChisq = chisq;
                     }
                  }else if( orderingOptArr_[0] == "dr" ){
                     if( bestTopJetIdx == -1 ){
                         bestTopJetIdx = ic;
                     }else if( finalCombMaxDR[bestTopJetIdx] > finalCombMaxDR[ic] ){
                         bestTopJetIdx = ic;
                     }
                  }else if( orderingOptArr_[0] == "mass" ){
                     if( bestTopJetIdx == -1 ){
                        bestTopJetIdx = ic;
                     }else{
                        double pickedTopMass = fatJetMassVec[bestTopJetIdx];
         // Find the configuration of an event (with a <top fat jet, tagged b-jet> combination) with
         // the best top mass of the top fat jet
                        if( fabs(pickedTopMass - mTop_) > fabs( fatJetm123 - mTop_ ) ){
                           bestTopJetIdx = ic;
                        }
                     }
                  }else if( orderingOptArr_[0] == "pt" ){
                     if( (int)ic<=maxIndexForOrderingArr_[0] ){
                        if( bestTopJetIdx == -1 ){
                           bestTopJetIdx = ic;
                        }
                     }
                  }else if( orderingOptArr_[0] == "hybrid" ){
                     if( (int)ic<=maxIndexForOrderingArr_[0] ){
                        if( bestTopJetIdx == -1 ){
                           bestTopJetIdx = ic;
                        }else{
                           double pickedTopMass = fatJetMassVec[bestTopJetIdx];
                           if( fabs(pickedTopMass - mTop_) > fabs( fatJetm123 - mTop_ ) ){
                              bestTopJetIdx = ic;
                           }
                        }
                     }
                  }
               }
            }

            if( bestTopJetIdx != -1 ){
               tmpModiforiJetsVec.clear(); tmpModifrecoJetsBtagCSVS.clear(); 
 
               std::vector<TLorentzVector> hepTaggerSubJetsVec = hepTaggerJetsVec[bestTopJetIdx];

               resolveOverlappingJets(oriJetsVec, recoJetsBtagCSVS, hepTaggerSubJetsVec, tmpremainingJetsVec, tmpremainingJetsBtagCSVS, hepTaggerSubJetsBtagCSVS);

               for(unsigned int ih=0; ih<hepTaggerSubJetsVec.size(); ih++){
                  tmpModiforiJetsVec.push_back( hepTaggerSubJetsVec[ih] );
                  tmpModifrecoJetsBtagCSVS.push_back( hepTaggerSubJetsBtagCSVS[ih] );
               }

               for(unsigned int io=0; io<tmpremainingJetsVec.size(); io++){
                  tmpModiforiJetsVec.push_back( oriJetsVec[tmpremainingJetsVec[io]] );
                  tmpModifrecoJetsBtagCSVS.push_back( tmpremainingJetsBtagCSVS[io] );
               }
            }else{
               tmpModiforiJetsVec.clear(); tmpModifrecoJetsBtagCSVS.clear(); 
            }
         }

         bool processEvent(const std::vector<TLorentzVector> &oriJetsVec, const std::vector<double> &recoJetsBtagCSVS, const TLorentzVector &metLVec, const std::vector<std::vector<TLorentzVector> > &hepTaggerJetsVec){

            int noriJets = oriJetsVec.size();

// Reset all variables to their default values
// before any further processing including nJetsSel verification!
            setDefaultVars();

            bool pass = true;

            if( noriJets < nJetsSel_ ) pass = false;
 
            if( noriJets >= nJetsSel_ ){

               prepareANDfindBestTopCandidate(oriJetsVec, recoJetsBtagCSVS, hepTaggerJetsVec, modiforiJetsVec, modifrecoJetsBtagCSVS);
               fillingBestTopCandidateVars(modiforiJetsVec, modifrecoJetsBtagCSVS);

// The number 3 is because we need 3 jets for the remaining triplet
               if( remainJetNum >= 3 ){
                  prepareFindingRemainingTopCandidate(modiforiJetsVec, modifrecoJetsBtagCSVS);
                  findRemainingTopCandidate(modiforiJetsVec, modifrecoJetsBtagCSVS);
                  fillingRemainingTopCandidate(modiforiJetsVec, modifrecoJetsBtagCSVS);
               }

               tunningRemainingJetSystem(modiforiJetsVec, modifrecoJetsBtagCSVS, metLVec);

               prepareCutVariables(modiforiJetsVec, modifrecoJetsBtagCSVS, metLVec);

               pass = applyCuts();

            }else{
               pass = false;
            }

            return pass;
         }

// For di-Top cases
// 
         void findDiTopCandidates(const std::vector<TLorentzVector> &oriJetsVec, const std::vector<double> &recoJetsBtagCSVS){
            for(int ic=0; ic<combSize; ic++){
               double fatJetm123 = fatJetMassVec[ic];
//               double fatJetm12 = buildLVec(oriJetsVec, finalCombJetSubStruc[ic][0]).M();
//               double fatJetm13 = buildLVec(oriJetsVec, finalCombJetSubStruc[ic][1]).M();
//               double fatJetm23 = buildLVec(oriJetsVec, finalCombJetSubStruc[ic][2]).M();
               
               vector<int> fatJetPassStatusVec;
               int isTopJet = checkTopCriteria(finalCombfatJets[ic], oriJetsVec, recoJetsBtagCSVS, fatJetSubMassVec[ic], fatJetm123, fatJetPassStatusVec);
               if( isTopJet ){
                  allCombPassCriteriaVec.push_back(ic);
               }
            }
         }

         int topTaggerLowPt(const std::vector<TLorentzVector> &oriJetsVec, const std::vector<double> &recoJetsBtagCSVS, vector<int> &pickedTopIdxVec){

            pickedTopIdxVec.clear();

            double minchisq = -1;
            for(unsigned int ij=0; ij<oriJetsVec.size()-1; ij++){
         
               if( recoJetsBtagCSVS[ij] > oriCSVScut_ && fabs(oriJetsVec[ij].Eta())< orimaxEtaForbJets_ ) continue;
         
               for(unsigned int jj=ij+1; jj<oriJetsVec.size(); jj++){

                  if( recoJetsBtagCSVS[jj] > oriCSVScut_ && fabs(oriJetsVec[jj].Eta())< orimaxEtaForbJets_ ) continue;
         
                  TLorentzVector WLVec = oriJetsVec[ij] + oriJetsVec[jj];
         
         //         if( WLVec.M() < lowWCut_ || WLVec.M() > highWCut_ ) continue;
         
                  double deltaPhiWDaus = fabs(TVector2::Phi_mpi_pi(oriJetsVec[ij].Phi() - oriJetsVec[jj].Phi()));
                  double deltaRWDaus = oriJetsVec[ij].DeltaR(oriJetsVec[jj]);
                  double deltaWmass = fabs( WLVec.M() - mW_ );
         
                  if( deltaPhiWDaus < 0.4 || deltaPhiWDaus > 3.2 ) continue;
                  if( deltaRWDaus < 0.8 || deltaRWDaus > 3.2 ) continue;
         
                  for(unsigned int kj=0; kj<oriJetsVec.size(); kj++){
                     if( kj == ij || kj == jj ) continue;

                     if( cntnbJetsCSVS >=2 ){ if( !(recoJetsBtagCSVS[kj] > CSVS_ && fabs(oriJetsVec[kj].Eta()) < maxEtaForbJets_ ) ) continue; }
                     else if( recoJetsBtagCSVS[kj] > CSVS_ && fabs(oriJetsVec[kj].Eta()) < maxEtaForbJets_ ) continue;
         
                     TLorentzVector topLVec = WLVec + oriJetsVec[kj];
         
                     if( topLVec.M() < lowTopCut_ || topLVec.M() > highTopCut_ ) continue;
         
                     double deltaPhibW = fabs(TVector2::Phi_mpi_pi(oriJetsVec[kj].Phi() - WLVec.Phi() ) );
                     double deltaRbW = oriJetsVec[kj].DeltaR(WLVec);
                     double deltaTopmass = fabs( topLVec.M() - mTop_ );
         
                     double maxDeltaRcover = 0;
                     if( maxDeltaRcover < topLVec.DeltaR( oriJetsVec[ij] ) ) maxDeltaRcover = topLVec.DeltaR( oriJetsVec[ij] );
                     if( maxDeltaRcover < topLVec.DeltaR( oriJetsVec[jj] ) ) maxDeltaRcover = topLVec.DeltaR( oriJetsVec[jj] );
                     if( maxDeltaRcover < topLVec.DeltaR( oriJetsVec[kj] ) ) maxDeltaRcover = topLVec.DeltaR( oriJetsVec[kj] );
         
                     if( deltaPhibW < 1.0 || deltaPhibW > 3.2 ) continue;
                     if( deltaRbW < 1.3 || deltaRbW > 3.2 ) continue;
                     if( maxDeltaRcover < 1.0 || maxDeltaRcover > 3.2 ) continue;
         
//                     double chisq = deltaTopmass*deltaTopmass*deltaWmass*deltaWmass;
                     double chisq = deltaTopmass*deltaTopmass + deltaWmass*deltaWmass;
                     if( minchisq == -1 ){
                        minchisq = chisq;
                        pickedTopIdxVec.push_back(ij); pickedTopIdxVec.push_back(jj); pickedTopIdxVec.push_back(kj);
                     }else if( minchisq > chisq ){
                        minchisq = chisq;
                        pickedTopIdxVec[0] = ij; pickedTopIdxVec[1] = jj; pickedTopIdxVec[2] = kj;
                     }
                  }
               }
            }
         
            return 1;
         }

// The tunning parameters
         void setdoExtraCuts(const bool doExtraCuts){ doExtraCuts_ = doExtraCuts; } 
         void setdoInvertTopCriteria(const bool doInvertTopCriteria){ doInvertTopCriteria_ = doInvertTopCriteria; } 
         void setmTbcut(const double mTbcut){ mTbcut_ = mTbcut; }
         void setmTtcut(const double mTtcut){ mTtcut_ = mTtcut; }
         void setMT2cut(const double MT2cut){ MT2cut_ = MT2cut; }
         void setmTWcut(const double mTWcut){ mTWcut_ = mTWcut; }
         void setdoMTMT2cuts( const bool doMTMT2cuts ){ doMTMT2cuts_ = doMTMT2cuts; }
         void setPDGmWmTop(const double mW, const double mTop){
            mW_ = mW; mTop_ = mTop; mWoverTop_ = mW_/mTop_;
            if( lowRatioWoverTop_ != -1 ) Rmin_ = lowRatioWoverTop_*mWoverTop_;
            if( highRatioWoverTop_ != -1 ) Rmax_ = highRatioWoverTop_*mWoverTop_;
         }
         void setlowRatioWoverTop(const double lowRatioWoverTop){ lowRatioWoverTop_ = lowRatioWoverTop; if( mWoverTop_ != -1 ) Rmin_ = lowRatioWoverTop_*mWoverTop_; }
         void sethighRatioWoverTop(const double highRatioWoverTop){ highRatioWoverTop_ = highRatioWoverTop; if( mWoverTop_ != -1 ) Rmax_ = highRatioWoverTop_*mWoverTop_; }
         void setlowArcTanm13overm12(const double lowArcTanm13overm12){ lowArcTanm13overm12_ = lowArcTanm13overm12; }
         void sethighArcTanm13overm12(const double highArcTanm13overm12){ highArcTanm13overm12_ = highArcTanm13overm12; }
         void setlowm23overm123(const double lowm23overm123){ lowm23overm123_ = lowm23overm123; }
         void setdefaultJetCone( const double defaultJetCone ){ defaultJetCone_ = defaultJetCone; }
         void setsimuCAdeltaR( const double simuCAdeltaR ){ simuCAdeltaR_ = simuCAdeltaR; }
         void setsimuCALargerdeltaR( const double simuCALargerdeltaR ){ simuCALargerdeltaR_ = simuCALargerdeltaR; }
         void setlowTopCut( const double lowTopCut ){ lowTopCut_ = lowTopCut; }
         void sethighTopCut( const double highTopCut ){ highTopCut_ = highTopCut; }
         void setlowWCut( const double lowWCut ){ lowWCut_ = lowWCut; }
         void sethighWCut( const double highWCut ){ highWCut_ = highWCut; }
         void setCSVS( const double CSVS ){ CSVS_ = CSVS; globalCachedCSVS_ = CSVS_; oriCSVScut_ = CSVS_; }
         void setnSubJetsDiv( const int nSubJetsDiv ){ nSubJetsDiv_ = nSubJetsDiv; }
         void setnJetsSel ( const int nJetsSel ){ nJetsSel_ = nJetsSel; }
         void setmaxEtaForbJets( const double maxEtaForbJets ){ maxEtaForbJets_ = maxEtaForbJets; orimaxEtaForbJets_ = maxEtaForbJets_; }
         void setorderingOptArr( const std::vector<std::string> & orderingOptArr ){ orderingOptArr_ = orderingOptArr; }
         void setorderingOptArr(){ std::vector<std::string> orderingOptArr(defaultOrderingOptArr, defaultOrderingOptArr+sizeof(defaultOrderingOptArr)/sizeof(defaultOrderingOptArr[0])); orderingOptArr_ = orderingOptArr; }
         void setmaxIndexForOrderingArr( const std::vector<int> & maxIndexForOrderingArr ){ maxIndexForOrderingArr_ = maxIndexForOrderingArr; }
         void setmaxIndexForOrderingArr(){ std::vector<int> maxIndexForOrderingArr(defaultMaxIndexForOrderingArr, defaultMaxIndexForOrderingArr+sizeof(defaultMaxIndexForOrderingArr)/sizeof(defaultMaxIndexForOrderingArr[0])); maxIndexForOrderingArr_ = maxIndexForOrderingArr; }
         void setmaxDRjetMatch(const double maxDRjetMatch){ maxDRjetMatch_ = maxDRjetMatch; }

         void setdebug( const bool debug ){ debug_ = debug; }
         void settaggingMode( const bool taggingMode ){ taggingMode_ = taggingMode; }

         void setdobVetoCS( const bool dobVetoCS ){
            dobVetoCS_ = dobVetoCS; globalCacheddobVetoCS_ = dobVetoCS_;
            if( dobVetoCS_ ){
               CSVS_ = minCSVS_disablebtag; globalCachedCSVS_ = CSVS_; 
               std::cout<<"\nINFO ... in setdobVetoCS function CSVS_ value is set to be : "<<CSVS_<<std::endl; 
               std::cout<<"Please make sure you alreay veto b outside of the top tagger, otherwise b information is completely ingored for the results from the top tagger!"<<std::endl<<std::endl;
            }
         }

         void setdoTopVeto( const bool doTopVeto ){
            doTopVetoSel_ = doTopVeto; 
            if( doTopVetoSel_ ){
               std::cout<<"\n\nINFO ... working on top veto case... NOTE that conditions in checkTopCriteria is altered in this case!"<<std::endl<<std::endl;
            }
         }

         void setbVetoMethod( const int bVetoMethod ){ bVetoMethod_ = bVetoMethod; }

         void setWjetMassRanges( const double lowWjetMass, const double highWjetMass ){ lowWjetMass_ = lowWjetMass; highWjetMass_ = highWjetMass; }

         void setdoWjetfatJets( const bool doWjetfatJets ){ doWjetfatJets_ = doWjetfatJets; }

         void setTopjetMassRanges( const double lowTopjetMass, const double highTopjetMass ){ lowTopjetMass_ = lowTopjetMass; highTopjetMass_ = highTopjetMass; }

         void setdoTopjetfatJets( const bool doTopjetfatJets ){ doTopjetfatJets_ = doTopjetfatJets; }

         void setdoCombTopTagger( const bool doCombTopTagger){ doCombTopTagger_ = doCombTopTagger; }

         void setlowTopPtToComb( const double lowTopPtToComb){ lowTopPtToComb_ = lowTopPtToComb; }

         void setgroomedJetsVec( const std::vector<TLorentzVector> groomedJetsVec ){ groomedJetsVec_ = groomedJetsVec; }

      private:

// doExtraCuts: extra cuts other than the top tagger related, e.g., dphi cuts, HT cut and so on.
         bool doExtraCuts_;

// doInvertTopCriteria: do inversion of top criteria or not. default is false.
         bool doInvertTopCriteria_;

         double mTbcut_, mTtcut_, MT2cut_, mTWcut_;
// doMTMT2cuts: numbers are counted. But if enabled, some plots will be filled after all the cuts.
         bool doMTMT2cuts_;

// PDG values (in GeV)
         double mW_, mTop_, mWoverTop_;

// double lowRatioWoverTop = 0.85, highRatioWoverTop = 1.15;
         double lowRatioWoverTop_, highRatioWoverTop_;
         double lowArcTanm13overm12_, highArcTanm13overm12_, lowm23overm123_;

         double Rmin_, Rmax_;

         double defaultJetCone_;
         double simuCAdeltaR_;
// Eta ranges from 0 to 5, phi ranges from 0 to 3.14.
// sqrt(5./2.*5./2. + 3.14/2. * 3.14/2.) ~ 2.95
// double simuCALargerdeltaR = 3.0;
         double simuCALargerdeltaR_; // -1 means no deltaR requirement

         double lowTopCut_, highTopCut_;
         double lowWCut_, highWCut_;

// Choose CSVM point for now
// --> A good top fat jet might indicate a b-jet already,
// so requiring another tight b-jet is NOT good. (TODO: to be studied)
//    double CSVL = 0.244, CSVM = 0.679, CSVT = 0.898;
         double CSVS_, globalCachedCSVS_;

         double oriCSVScut_, orimaxEtaForbJets_;

         int nSubJetsDiv_;

         int nJetsSel_;

         double maxEtaForbJets_;

// mass   : mass ordering --> pick the one with mass closest to the norminal mass
// pt     : pt ordering --> pick the one with larger pt (for the first two fat jets)
// hybrid : pt ordering + mass ordering --> if both of the first two fat jets
//          satisfying criteria, pick the one closer to the norminal mass
         std::vector<std::string> defaultOrderingOptVec;
//                                                     best   remaining
         std::vector<std::string>  orderingOptArr_; // (mass, mass) is the best?

         std::vector<int> defaultMaxIndexForOrderingVec;
         std::vector<int> maxIndexForOrderingArr_;

// The max DR for jet matching between ak5 jets and subjets from HEPTopTagger
         double maxDRjetMatch_;

         bool debug_;

         bool taggingMode_;

// For the b-veto Control Sample
         bool dobVetoCS_, globalCacheddobVetoCS_;
// default bVetoMethod_ = 0 which is to assign the highest CSV jet as a b jet (no need set dobVetoCS_ to be true)
// 1 : force the CSVS_ cut to be -1e10 so that very jet is condsidered as a b jet
         int bVetoMethod_;
// For top veto
         bool doTopVetoSel_;

// Mass ranges for picking a W jet
// Default: lowWjetMass_ = 70, highWjetMass_ = 110. They come from reading the mass distributions of the signal samples.
// The range here is quite loose.
         double lowWjetMass_, highWjetMass_;
         bool doWjetfatJets_;
         double lowTopjetMass_, highTopjetMass_;
         bool doTopjetfatJets_;

         bool doCombTopTagger_;
         double lowTopPtToComb_;
   };

}

#endif
