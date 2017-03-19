require barebox-common.inc

SUMMARY = ""
DESCRIPTION = ""

DEPENDS += "virtual/libc"

SRC_URI += " \
    file://target-utils.cfg \
"

PACKAGE_ARCH="${TUNE_PKGARCH}"

export TARGETCFLAGS="${TARGET_CC_ARCH} ${TOOLCHAIN_OPTIONS} ${CFLAGS} ${LDFLAGS}"

do_install() {
    for i in bareboxcrc32 bareboxenv bareboximd kernel-install
    do
        src="${B}/scripts/${i}-target"
        if [ -f "${src}" ]
        then
            case "${i}" in
                barebox*)
                    dest=${i}
                    ;;
                *)
                    dest="barebox-${i}"
                    ;;
            esac
            install -m 755 "${src}" "${D}/${sbindir}/${dest}"
        fi
    done
}
do_install[dirs] += "${D}/${sbindir}"

do_deploy[noexec] = "1"

COMPATIBLE_MACHINE = "${COMPATIBLE_MACHINE_pn-barebox}"
