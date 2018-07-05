#!/bin/bash

TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
SRCDIR=${SRCDIR:-$TOPDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

SYNDICATED=${SYNDICATED:-$SRCDIR/syndicated}
SYNDICATECLI=${SYNDICATECLI:-$SRCDIR/syndicate-cli}
SYNDICATETX=${SYNDICATETX:-$SRCDIR/syndicate-tx}
SYNDICATEQT=${SYNDICATEQT:-$SRCDIR/qt/syndicate-qt}

[ ! -x $SYNDICATED ] && echo "$SYNDICATED not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
BTCVER=($($SYNDICATECLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }'))

# Create a footer file with copyright content.
# This gets autodetected fine for syndicated if --version-string is not set,
# but has different outcomes for syndicate-qt and syndicate-cli.
echo "[COPYRIGHT]" > footer.h2m
$SYNDICATED --version | sed -n '1!p' >> footer.h2m

for cmd in $SYNDICATED $SYNDICATECLI $SYNDICATETX $SYNDICATEQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${BTCVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${BTCVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
