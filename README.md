# HLT_Run3


### Environment set-up

	cmsrel CMSSW_12_3_0_pre4;
	cd CMSSW_12_3_0_pre4/src;
	cmsenv;

### TSG Rate Studies
#### Get the tool


	git clone https://github.com/sanuvarghese/SteamRatesEdmWorkflow.git 

#### Create the EDM files from Ephemeral dataset


	cp Rates_TSG/hlt.py SteamRatesEdmWorkflow/Prod/ ;
	cp Rates_TSG/list_cff.py SteamRatesEdmWorkflow/Prod/ ;
	cp Rates_TSG/json_323775.txt SteamRatesEdmWorkflow/Rates/ ;
	cp Rates_TSG/config_makeCondorJobsData.py SteamRatesEdmWorkflow/Rates/ ;
	cd SteamRatesEdmWorkflow/Prod/ ;
	edmConfigDump hlt.py > hlt_config.py;
	./cmsCondorData.py run_steamflow_cfg.py <your CMSSW/src env> <Where you will store EDM files> -n 1 -q longlunch;
	./sub_total.jobb; #to submit jobs

#### Prepare the counting script

	cd ../Rates/ ;

##### Modify the values of **inputFilesDir**, **cmsswDir**, and **json_file** in *config_makeCondorJobsData.py* to match your setup

#### Run the counting scripts

	cd ../Rates/ ;
	

### Efficiency Studies

- one 

- two

#### Timing Studies

- one 

- two
