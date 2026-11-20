Advantech BSP for Qualcomm based boards
=======================================

This layer adds minimal changes on top of Qualcomm Linux BSP to support Advantech boards, with the purpose of leveraging that for easier long term maintenance.

For build pre-requisites check [README in the Qualcomm Linux releases repository](https://github.com/qualcomm-linux/meta-qcom-releases/tree/qli-2.0).

Simple build example using Qualcomm's distribution plus the Advantech layer:

```
RTAG=qli-2.0             # Or e.g., RTAG=qli-2.1 (not tested), RTAG=qli-2.1.1 (build issues)
RTAG_ADV=wrynose-test2   # E.g., using 'wrynose-test2' branch. We'll match QC's tags, e.g. using `RTAG_ADV=$RAG`
QC_R=meta-qcom-releases
QC_M=meta-modular-bsp-qcom
QC_CI=meta-qcom/ci

git clone https://github.com/qualcomm-linux/$QC_R -b $RTAG
git clone https://github.com/Advantech-EECC/$QC_M -b $RTAG_ADV

kas checkout $QC_R/lock.yml

cp "$QC_R/lock.yml" "$QC_M/$QC_M.yml" "$QC_CI/"

IMAGE=qcom-multimedia-proprietary-image
KAS_LIST=$QC_CI/base.yml:$QC_CI/qcom-distro.yml:$QC_CI/lock.yml:$QC_CI/$QC_M.yml

KAS_MACHINE=aom5721-qcs6490-db6700 kas shell "$KAS_LIST" -c "bitbake $IMAGE"
```

To flash the image, e.g.

```
# Set boot mode in SW2 (AOM-DB6700) to: 100100 (recovery) + power cycle
cd build/tmp/deploy/images/aom5721-qcs6490-db6700/qcom-multimedia-proprietary-image-aom5721-qcs6490-db6700.rootfs.qcomflash
qdl --storage ufs prog_firehose_ddr.elf rawprogram[0-9].xml patch[0-9].xml
# Set boot mode in SW2 (AOM-DB6700) to: 100000 (UFS boot) + power cycle
```

Observations:
- For the preliminary support currently we target only 'qli-2.0' release. Our intention is having a layer that follow easily from Qualcomm's updates.
- The `core-image-minimal` (Yocto base) has no root password
- The `qcom-multimedia-proprietary-image` root password is Qualcomm's default, i.e. `oelinux123`

Supported Boards
================

Preliminary support:

 * AOM-5721-A1-QCS6490 8GB (`aom5721-qcs6490-db6700`, SMARC 2.2 on AOM-DB6700-A1)

Supported Linux Features
========

AOM-5721-A1-QCS6490 (on AOM-DB6700-A1, SMARC 2.2 carrier board)
--------

| Device   | Status | Comment |
|----------|--------|---------|
| UFS      |  ✅ | As /dev/sda |
| SDHC     |  ✅ | As /dev/mmcblk2 |
| ETH0     |  ✅ | PCIE 1Gbps Ethernet |
| ETH1     |  ✅ | PCIE 1Gbps Ethernet |
| UART5    |  ✅ | COM3 Linux Console (/dev/ttyMSM0) |
| UART6    |  ⚠️  | COM0 (4-wire), not tested (/dev/ttyHS1) |
| UART10   |  ⚠️  | COM2 (4-wire), not tested (/dev/ttyHS2) |
| UART11   |  ⚠️  | COM1 (2-wire), not tested (/dev/ttyHS3) |
| USB2-1   |  ✅ | USB 2.0 (480Mbps) |
| USB2-1   |  ✅ | USB 2.0 (480Mbps) |
| HDMI     |  ✅ |  |
| DP       |  ❌ |  |
| eDP      |  ❌ |  |
| MIPI-CSI |  ⚠️  | 2x connectors available; no camera connected |
| I2C-0    |  ⚠️  | Not tested |
| I2C-1    |  ✅ |  |
| I2C-3    |  ✅ |  |
| I2C-9    |  ⚠️  | Not tested |
| NPU      |  ⚠️  | Work in progress - "working" by adding DSP library symlinks manually |
| CAN0     |  ⚠️  | Not tested |
| CAN1     |  ⚠️  | Not tested |
| PCIE     |  ✅ | Qualcomm SM8250 PCIE Root Complex |
| PCIE-M2  |  ❌ |  |
| GPIO     |  ✅ | 2x TCA9555 (I2C1 0x27, I2C3 0x27) |
| RTC0     |  ✅ | RX8900 I2C RTC |
| RTC1     |  ✅ | PMK8350 built-in RTC |
| SPI-7    |  ✅ | 8MB SPI-NOR as /dev/mtd0 |
| SPI-12   |  ❌ |  |
| TPM      |  ✅ |  |
| Watchdog |  ✅ | Built-in watchdog |
