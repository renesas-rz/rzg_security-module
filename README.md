# README of the RZ/G Security Module

<Div Align="right">
Renesas Electronics Corporation

Jul-06-2021
</Div>

The RZ/G Security Module is sample software for Renesas RZ/G2 Group MPUs.
The RZ/G Security Module provides functions related to a Secure Boot.

## 1. Overview

This document explains about the RZ/G Security Module sample software for Renesas RZ/G Group MPUs.

The RZ/G Security Module provides the following functions related to a Secure Boot.

  - Keyring Re-Encryption
  - User Data Re-Encryption
  - Keyring Verification
  - User Data Verification

## 1.1 License

  - BSD-3-Clause (please see file [LICENSE.txt](LICENSE.txt) for the details)

## 1.2 Requirement

  - RZ/G2 Secure IP library v2.1.0

## 1.3. Notice

The RZ/G Security Module is distributed as a sample software from Renesas without any warranty or support.

For inquiries regarding the provision of the RZ/G2 Secure IP Library, please contact Renesas Electronics distributor or contact us.

## 1.4. Contributing

To contribute to this software, you should email patches to renesas-rz@renesas.com. Please send .patch files as email attachments, not embedded in the email body.

## 1.5. References

The following table shows the document related to this function.

| Number | Issuer  | Title                                                          | Edition           |
|--------|---------|----------------------------------------------------------------|-------------------|
| 1      | Renesas | RZ/G2 Trusted Execution Environment Start-Up Guide             | Rev.1.00 or later |
| 2      | Renesas | RZ/G2 Trusted Execution Environment Porting Guide              | Rev.1.00 or later |

## 2. Operating Environment

### 2.1. Hardware Environment

The following table lists the hardware needed to use this utility.

#### Hardware environment

| Name         | Note                                        |
|--------------|---------------------------------------------|
| Target board | Hoperun HiHope RZ/G2[M,N,H] platform        |
|              | Silicon Linux RZ/G2E evaluation kit (EK874) |

### 2.2. Software Environment

The following table lists the software required to use this sample software.

#### Software environment

| Name                | Note                                                             |
|---------------------|------------------------------------------------------------------|
| Linaro Toolchain *1 | Linaro Binary Toolchain Release GCC 7.3-2018.05 for aarch64-elf. |
| Yocto SDK *1        | Yocto SDK built from Yocto environment for RZ/G2 Group           |

\*1: One of the above toolchains are required.

## 3. Software

### 3.1. Software Function

The RZ/G Security Module has the following functions:

  - Keyring Re-Encryption
  - User Data Re-Encryption
  - Keyring Verification
  - User Data Verification

#### 3.1.1. Keyring Re-Encryption

This function re-encrypts the Keyring that were temporarily encrypted in the external environment(Host PC) using a device-specific key.

#### 3.1.2. User Data Re-Encryption

This function re-encrypts the User Data that were temporarily encrypted in the external environment(Host PC) using a device-specific key.

#### 3.1.3. Keyring Verification

This function verifies that the re-encrypted Keyring has not been tampered with.
If the validation fails, an error is returned.
Verification of the re-encrypted Keyring must be done before verification of the re-encrypted User Data.

#### 3.1.4. User Data Verification

This function decrypts and validates the re-encrypted User Data.
If the validation fails, an error is returned.


### 4. How to Build

### 4.1. Option setting

The RZ/G Security Module support the following build options.

#### 4.1.1. LSI

Select from the following according to the target RZ/G2 device.

  - G2E
  - G2M
  - G2N
  - G2H

#### 4.1.2. SEC_LIB_DIR

Specify the path of the directory where the RZ/G2 Secure IP library is stored.

### 4.2. Prepare the compiler

Gets cross compiler for linaro or setup the Yocto SDK.

Linaro toolchain:

```shell
cd ~/
wget https://releases.linaro.org/components/toolchain/binaries/7.3-2018.05/aarch64-elf/gcc-linaro-7.3.1-2018.05-x86_64_aarch64-elf.tar.xz
tar xvf gcc-linaro-7.3.1-2018.05-x86_64_aarch64-elf.tar.xz
```

Yocto SDK:

```shell
source /opt/poky/2.4.3/environment-setup-aarch64-poky-linux
```

### 4.3. Prepare the source code

Get the source code of RZ/G Security Module.

```shell
cd ~/
git clone https://github.com/renesas-rz/rzg_security-module.git
cd rzg_security-module
git checkout -b v1.01
```

### 4.4. Build the RZ/G Security Module

S-record file will be built by the following command.

Linaro toolchain:

```shell
make clean
CROSS_COMPILE=~/gcc-linaro-7.3.1-2018.05-x86_64_aarch64-elf/bin/aarch64-elf- make LSI=G2X SEC_LIB_DIR=<dir-path>
```

Yocto SDK:

```shell
make clean
make LSI=G2X SEC_LIB_DIR=<dir-path>
```

Output image will be available in the following directory.

* ./out/sec_module.srec


## 5. How to run the RZ/G Security Module

### 5.1 Loading

  - Load the Security Module at 0x440E0000 address in the SDRAM.

### 5.2 Run

The RZ/G security module has a shared area with external software in the area of 0x200 bytes from the load address.

The Entry point of the RZ/G Security Module is placed immediately after this shared area.

For external software to call the RZ/G security module, follow these steps:
  1. Set the parameters of the st_sec_module_arg_t structure into the shared area.
  2. Jump to the Entry Point.

```shell
                         RZ/G Security Module
0x440E0000 - +--------------------------------------------+
             |                Shared Area                 |
             |  ( Set the st_sec_module_arg_t structure ) |
0x440E0200 - +--------------------------------------------+ <- Entry Point
             |                                            |
             |                                            |
```

## 6. Revision history

Describe the revision history of RZ/G Security Module.

### 6.1. v1.00

- First release.

### 6.1. v1.01

- TSIP Driver: Fix unalignment access.
