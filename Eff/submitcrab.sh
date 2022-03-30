#voms-proxy-init --voms cms --valid 100:00
# submit or just generate submit scripts
dosubmit=true
# Give the submission a name
version=Test

# start the timer
START=$(date +%s);
printf "Started at ${START}\n\n"

# make the directory where we'll submit from
thesubdir="$PWD/gitignore/${version}"
mkdir -p ${thesubdir}
printf "Making submit configurations in\n ${thesubdir}\n\n"

# copy necessary files into submit directory
submitconfig="hltRun3Summer21MC.py"
thedasmap="dasmap.list"

# copy cmsRun configuration to submit directory
cp "${submitconfig}"  ${thesubdir}


# sample names to run over
samples=( \
"ggHH4b_cHHH1"                   \
#"ggHH4b_cHHH2p45"                   \
#"ggHH4b_cHHH5"                   \
)

# print which samples we're running over
printf "For:\n"
for samplename in ${samples[@]}
do
 printf " ${samplename}\n"
done

# loop over mc samples
for samplename in ${samples[@]}
do
 printf "\n******************************************************\n"
 if [ ${dosubmit} = true ]
 then
  printf "** \n"
  printf "** --- SUBMITTING --- \n"
  printf "** \n"
 fi
 printf "** Sample: ${samplename} \n"
 printf "******************************************************\n"
 printf "******************************************************\n\n"

 echo "$(grep -P ${samplename} ${thedasmap})"
 echo "$(grep -P ${samplename} ${thedasmap} | sed -n -e "s@ ${samplename}    @@p")"
 datasetname="$(grep -P ${samplename} ${thedasmap} | sed -n -e "s@ ${samplename}    @@p")"
 
 submitname="submit_${samplename}"
 submitfile="${thesubdir}/${submitname}.py"

 # set variables for submitting this specific sample
 WORKAREA="'crabsubmits_${version}'"

 ## lumi mask
 LUMIMASK=""

 # choose correct config parameters
 CMSRUNCONFIG="'${submitconfig}'"
 UPERJOB="180"
 #SPLITTING="'FileBased'"
 SPLITTING="'Automatic'"

 NUNITS="1000"
 #NUNITS="-1"
 REQUESTNAME="'${samplename}'"
 DATASET="'${datasetname}'"
 #STORESITE="'T3_US_FNALLPC'"
 STORESITE="'T2_CH_CERN'"
# if [ ${do_lpchbb} = true ]
# then
#     OUTLFNBASE="'/store/group/lpchbb/LLDJntuples/${version}'"
# else
#     OUTLFNBASE="'/store/user/d/ddiaz/HLT_Run3/${version}'"
# fi
 OUTLFNBASE="'/store/user/d/ddiaz/HLT_Run3/${version}'"
 MAXMEM="5000"

 printf "WORKAREA      ${WORKAREA}     \n"
 printf "CMSRUNCONFIG  ${CMSRUNCONFIG} \n"
 printf "NUNITS        ${NUNITS}       \n"
 printf "UPERJOB       ${UPERJOB}      \n"
 printf "SPLITTING     ${SPLITTING}    \n"
 printf "REQUESTNAME   ${REQUESTNAME}  \n"
 printf "DATASET       ${DATASET}      \n"
 printf "LUMIMASK      ${LUMIMASK}     \n"
 printf "STORESITE     ${STORESITE}    \n"
 printf "OUTLFNBASE    ${OUTLFNBASE}   \n"
 printf "MAXMEM        ${MAXMEM}       \n"

 # copy and then fill template for crab submits
 cp crab_template.py                       "${submitfile}"
 sed -i "s@WORKAREA@${WORKAREA}@g"         "${submitfile}"
 sed -i "s@CMSRUNCONFIG@${CMSRUNCONFIG}@g" "${submitfile}"
 sed -i "s@NUNITS@${NUNITS}@g"             "${submitfile}"
 sed -i "s@UPERJOB@${UPERJOB}@g"           "${submitfile}"
 sed -i "s@SPLITTING@${SPLITTING}@g"       "${submitfile}"
 sed -i "s@REQUESTNAME@${REQUESTNAME}@g"   "${submitfile}"
 sed -i "s@DATASET@${DATASET}@g"           "${submitfile}"
 sed -i "s@LUMIMASK@${LUMIMASK}@g"         "${submitfile}"
 sed -i "s@STORESITE@${STORESITE}@g"       "${submitfile}"
 sed -i "s@OUTLFNBASE@${OUTLFNBASE}@g"     "${submitfile}"
 sed -i "s@MAXMEM@${MAXMEM}@g"             "${submitfile}"
 sed -i "/config.Data.lumiMask/d"          "${submitfile}"

 # submit the jobs
 if [ ${dosubmit} = true ]
 then
  pushd ${thesubdir} > /dev/null
  python ${submitfile}
  popd > /dev/null
 fi

done

# end the timer
END=$(date +%s);
printf "\nStarted at ${START}\n"
printf "Ended at   ${END}\n\n"
