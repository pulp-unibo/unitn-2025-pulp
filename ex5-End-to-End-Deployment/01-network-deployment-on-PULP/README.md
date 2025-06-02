# [APAI22-LAB09] End-to-end CNN deployment 


# 1. Setup

## Access to the remote server, and setup
1. Open this web page: https://compute.eees.dei.unibo.it:8443/guacamole/    (works only from ALMA WIFI NETWORK!).
2. Login with your credentials

## Download the repo
```
$ cd <work_dir>
$ git clone https://github.com/EEESlab/APAI23-LAB09-end-to-end-CNN-deployment.git --recurse-submodules --shallow-submodules
```

**Note**: make sure to clone with `--recurse-submodules` !

## Load modules
Load appropriate modules to be able to compile and run the code 

Note: Always do this when opening a new terminal session

```
$ module load pulp-sdk
$ module load dory-conda
```


# 2. How to run the code


#### 1. `cd` to dory directory
   
`$ cd APAI23-LAB09-end-to-end-CNN-deployment/dory`

#### 2. Generate the network

```
$ python network_generate.py Quantlab <target> ../<network>/config.json --perf_layer
```


The `target` can be:

* `PULP.PULP_gvsoc` - 8-core cluster execution
* `PULP.PULP_NE16` - NE16 execution


The `network` can be:

* `Network1` - network with a 3x3 convolution for the last layer

* `Network2` - network with a 5x5 convolution for the last layer

#### 3. Build and run the code

   
`$ make -C application clean all run CORE=8`
