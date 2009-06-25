#############################################################################
# Makefile for building: bin/Nutsh
# Generated by qmake (2.01a) (Qt 4.5.1) on: jeu. juin 25 21:02:34 2009
# Project:  nutsh-05.pro
# Template: app
# Command: /usr/bin/qmake -spec /usr/local/Qt4.5/mkspecs/macx-g++ -macx CONFIG+=debug_and_release -o Makefile nutsh-05.pro
#############################################################################

first: debug
install: debug-install
uninstall: debug-uninstall
MAKEFILE      = Makefile
QMAKE         = /usr/bin/qmake
DEL_FILE      = rm -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
COPY          = cp -f
COPY_FILE     = cp -f
COPY_DIR      = cp -f -R
INSTALL_FILE  = $(COPY_FILE)
INSTALL_PROGRAM = $(COPY_FILE)
INSTALL_DIR   = $(COPY_DIR)
DEL_FILE      = rm -f
SYMLINK       = ln -sf
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
SUBTARGETS    =  \
		debug \
		release

debug: $(MAKEFILE).Debug FORCE
	$(MAKE) -f $(MAKEFILE).Debug
debug-make_default: $(MAKEFILE).Debug FORCE
	$(MAKE) -f $(MAKEFILE).Debug 
debug-make_first: $(MAKEFILE).Debug FORCE
	$(MAKE) -f $(MAKEFILE).Debug first
debug-all: $(MAKEFILE).Debug FORCE
	$(MAKE) -f $(MAKEFILE).Debug all
debug-clean: $(MAKEFILE).Debug FORCE
	$(MAKE) -f $(MAKEFILE).Debug clean
debug-distclean: $(MAKEFILE).Debug FORCE
	$(MAKE) -f $(MAKEFILE).Debug distclean
debug-install: $(MAKEFILE).Debug FORCE
	$(MAKE) -f $(MAKEFILE).Debug install
debug-uninstall: $(MAKEFILE).Debug FORCE
	$(MAKE) -f $(MAKEFILE).Debug uninstall
release: $(MAKEFILE).Release FORCE
	$(MAKE) -f $(MAKEFILE).Release
release-make_default: $(MAKEFILE).Release FORCE
	$(MAKE) -f $(MAKEFILE).Release 
release-make_first: $(MAKEFILE).Release FORCE
	$(MAKE) -f $(MAKEFILE).Release first
release-all: $(MAKEFILE).Release FORCE
	$(MAKE) -f $(MAKEFILE).Release all
release-clean: $(MAKEFILE).Release FORCE
	$(MAKE) -f $(MAKEFILE).Release clean
release-distclean: $(MAKEFILE).Release FORCE
	$(MAKE) -f $(MAKEFILE).Release distclean
release-install: $(MAKEFILE).Release FORCE
	$(MAKE) -f $(MAKEFILE).Release install
release-uninstall: $(MAKEFILE).Release FORCE
	$(MAKE) -f $(MAKEFILE).Release uninstall

Makefile: nutsh-05.pro  /usr/local/Qt4.5/mkspecs/macx-g++/qmake.conf /usr/local/Qt4.5/mkspecs/common/unix.conf \
		/usr/local/Qt4.5/mkspecs/common/mac.conf \
		/usr/local/Qt4.5/mkspecs/common/mac-g++.conf \
		/usr/local/Qt4.5/mkspecs/qconfig.pri \
		/usr/local/Qt4.5/mkspecs/features/qt_functions.prf \
		/usr/local/Qt4.5/mkspecs/features/qt_config.prf \
		/usr/local/Qt4.5/mkspecs/features/exclusive_builds.prf \
		/usr/local/Qt4.5/mkspecs/features/default_pre.prf \
		/usr/local/Qt4.5/mkspecs/features/mac/default_pre.prf \
		/usr/local/Qt4.5/mkspecs/features/mac/dwarf2.prf \
		/usr/local/Qt4.5/mkspecs/features/debug.prf \
		/usr/local/Qt4.5/mkspecs/features/debug_and_release.prf \
		/usr/local/Qt4.5/mkspecs/features/default_post.prf \
		/usr/local/Qt4.5/mkspecs/features/mac/default_post.prf \
		/usr/local/Qt4.5/mkspecs/features/mac/objective_c.prf \
		/usr/local/Qt4.5/mkspecs/features/warn_on.prf \
		/usr/local/Qt4.5/mkspecs/features/qt.prf \
		/usr/local/Qt4.5/mkspecs/features/unix/thread.prf \
		/usr/local/Qt4.5/mkspecs/features/moc.prf \
		/usr/local/Qt4.5/mkspecs/features/mac/rez.prf \
		/usr/local/Qt4.5/mkspecs/features/mac/sdk.prf \
		/usr/local/Qt4.5/mkspecs/features/resources.prf \
		/usr/local/Qt4.5/mkspecs/features/uic.prf \
		/usr/local/Qt4.5/mkspecs/features/yacc.prf \
		/usr/local/Qt4.5/mkspecs/features/lex.prf \
		/usr/local/Qt4.5/mkspecs/features/include_source_dir.prf \
		/Library/Frameworks/phonon.framework/phonon.prl \
		/Library/Frameworks/QtDBus.framework/QtDBus.prl \
		/Library/Frameworks/QtXml.framework/QtXml.prl \
		/Library/Frameworks/QtCore.framework/QtCore.prl \
		/Library/Frameworks/QtGui.framework/QtGui.prl \
		/Library/Frameworks/QtSql.framework/QtSql.prl \
		/Library/Frameworks/QtNetwork.framework/QtNetwork.prl
	$(QMAKE) -spec /usr/local/Qt4.5/mkspecs/macx-g++ -macx CONFIG+=debug_and_release -o Makefile nutsh-05.pro
/usr/local/Qt4.5/mkspecs/common/unix.conf:
/usr/local/Qt4.5/mkspecs/common/mac.conf:
/usr/local/Qt4.5/mkspecs/common/mac-g++.conf:
/usr/local/Qt4.5/mkspecs/qconfig.pri:
/usr/local/Qt4.5/mkspecs/features/qt_functions.prf:
/usr/local/Qt4.5/mkspecs/features/qt_config.prf:
/usr/local/Qt4.5/mkspecs/features/exclusive_builds.prf:
/usr/local/Qt4.5/mkspecs/features/default_pre.prf:
/usr/local/Qt4.5/mkspecs/features/mac/default_pre.prf:
/usr/local/Qt4.5/mkspecs/features/mac/dwarf2.prf:
/usr/local/Qt4.5/mkspecs/features/debug.prf:
/usr/local/Qt4.5/mkspecs/features/debug_and_release.prf:
/usr/local/Qt4.5/mkspecs/features/default_post.prf:
/usr/local/Qt4.5/mkspecs/features/mac/default_post.prf:
/usr/local/Qt4.5/mkspecs/features/mac/objective_c.prf:
/usr/local/Qt4.5/mkspecs/features/warn_on.prf:
/usr/local/Qt4.5/mkspecs/features/qt.prf:
/usr/local/Qt4.5/mkspecs/features/unix/thread.prf:
/usr/local/Qt4.5/mkspecs/features/moc.prf:
/usr/local/Qt4.5/mkspecs/features/mac/rez.prf:
/usr/local/Qt4.5/mkspecs/features/mac/sdk.prf:
/usr/local/Qt4.5/mkspecs/features/resources.prf:
/usr/local/Qt4.5/mkspecs/features/uic.prf:
/usr/local/Qt4.5/mkspecs/features/yacc.prf:
/usr/local/Qt4.5/mkspecs/features/lex.prf:
/usr/local/Qt4.5/mkspecs/features/include_source_dir.prf:
/Library/Frameworks/phonon.framework/phonon.prl:
/Library/Frameworks/QtDBus.framework/QtDBus.prl:
/Library/Frameworks/QtXml.framework/QtXml.prl:
/Library/Frameworks/QtCore.framework/QtCore.prl:
/Library/Frameworks/QtGui.framework/QtGui.prl:
/Library/Frameworks/QtSql.framework/QtSql.prl:
/Library/Frameworks/QtNetwork.framework/QtNetwork.prl:
qmake: qmake_all FORCE
	@$(QMAKE) -spec /usr/local/Qt4.5/mkspecs/macx-g++ -macx CONFIG+=debug_and_release -o Makefile nutsh-05.pro

qmake_all: FORCE

make_default: debug-make_default release-make_default FORCE
make_first: debug-make_first release-make_first FORCE
all: debug-all release-all FORCE
clean: debug-clean release-clean FORCE
distclean: debug-distclean release-distclean FORCE
	-$(DEL_FILE) Makefile

debug-mocclean: $(MAKEFILE).Debug
	$(MAKE) -f $(MAKEFILE).Debug mocclean
release-mocclean: $(MAKEFILE).Release
	$(MAKE) -f $(MAKEFILE).Release mocclean
mocclean: debug-mocclean release-mocclean

debug-mocables: $(MAKEFILE).Debug
	$(MAKE) -f $(MAKEFILE).Debug mocables
release-mocables: $(MAKEFILE).Release
	$(MAKE) -f $(MAKEFILE).Release mocables
mocables: debug-mocables release-mocables
FORCE:

$(MAKEFILE).Debug: Makefile
$(MAKEFILE).Release: Makefile
