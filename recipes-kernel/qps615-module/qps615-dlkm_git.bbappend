FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI:append:aom5721 = " \
    file://0001-tc956x-qcom-Accept-RGMII-and-RGMII-ID-from-phy-mode.patch \
    file://0002-tc956x-Prevent-polled-PHY-work-and-preload-Realtek.patch \
"
