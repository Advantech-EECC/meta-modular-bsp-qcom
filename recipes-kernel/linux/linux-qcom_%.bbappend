FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:${THISDIR}/${PN}/${MACHINE}:${THISDIR}/${PN}/common:"

include recipes-kernel/linux/linux-qcom/${MACHINE}.inc
