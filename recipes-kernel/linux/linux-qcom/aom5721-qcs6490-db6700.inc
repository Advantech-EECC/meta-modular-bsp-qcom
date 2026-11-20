SRC_URI:append = " \
    file://${MACHINE}.dts \
    file://board.cfg \
    file://0011-Driver-NET-Add-advantech-s-rtl8211f-phy-led-setting.patch \
    ${@' '.join(['file://%s.dtso' % x for x in (d.getVar('DTBOS_EXTRA') or '').split()])} \
"

EXTRA_OEMAKE += "DTC_FLAGS=-@"

do_configure:prepend:aom5721() {
    cp "${UNPACKDIR}/"*\.dts* "${S}/arch/arm64/boot/dts/qcom/"

    tgt="${S}/arch/arm64/boot/dts/qcom/Makefile"

    tag="+= ${KERNEL_DEVICETREE_BASENAME}.dtb"
    grep -q "$tag" "$tgt" || echo "dtb-\$(CONFIG_ARCH_QCOM) $tag" >>"$tgt"

    for di in ${DTBOS_EXTRA} ; do
        tag="+= $di.dtbo"
        grep -q "$tag" "$tgt" || echo "dtb-\$(CONFIG_ARCH_QCOM) $tag" >>"$tgt"
    done
}
