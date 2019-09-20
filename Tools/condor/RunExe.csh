#!/bin/csh -v

set SCRAM = DELSCR
set CMSSW = DELDIR
set EXE   = DELEXE
set OUTPUT = OUTDIR

#============================================================================#
#-----------------------------   Setup the env   ----------------------------#
#============================================================================#
echo "============  Running on" $HOST " ============"
cd ${_CONDOR_SCRATCH_DIR}
source /cvmfs/cms.cern.ch/cmsset_default.csh
setenv SCRAM_ARCH ${SCRAM}
eval `scramv1 project CMSSW ${CMSSW}`
cd ${CMSSW}
eval `scramv1 runtime -csh` # cmsenv is an alias not on the workers
echo "CMSSW: "$CMSSW_BASE
cd ${_CONDOR_SCRATCH_DIR}

foreach tarfile (`ls *gz FileList/*gz`)
  echo $tarfile
  tar -xzf $tarfile 
end

if ! $?LD_LIBRARY_PATH then
    setenv LD_LIBRARY_PATH ./
else
    setenv LD_LIBRARY_PATH ./:${LD_LIBRARY_PATH}
endif
echo "ls ${CMSSW_BASE}/src/TopTagger/TopTagger/test/"
ls ${CMSSW_BASE}/src/TopTagger/TopTagger/test/
setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:${CMSSW_BASE}/src/TopTagger/TopTagger/test/
echo "LD_LIBRARY_PATH is "${LD_LIBRARY_PATH}

#============================================================================#
#--------------------------   To Run the Process   --------------------------#
#============================================================================#
cd ${CMSSW_BASE}/src/SusyAnaTools/Tools/
echo "pwd: "
pwd
cp ${_CONDOR_SCRATCH_DIR}/$argv[1] $argv[1]
echo "ls ${CMSSW_BASE}/src/SusyAnaTools/Tools/"
ls
echo $EXE $argv
./$EXE $argv

if ($? == 0) then
  rm 2016_trigger_eff.root
  rm 2017_trigger_eff.root
  rm 2018_trigger_eff.root
  rm PileupHistograms_Nov17.root
  rm test.root
  foreach tarfile (`ls *gz FileList/*gz`)
    tar -tf $tarfile  | xargs rm -r
  end
  foreach outfile (`ls *root`)
    echo "Copying ${outfile} to ${OUTPUT}"
    xrdcp $outfile "root://cmseos.fnal.gov/${OUTPUT}"
    if ($? == 0) then
      rm $outfile
    endif
  end
endif

