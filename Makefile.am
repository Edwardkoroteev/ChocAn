# Put m4 processing files in the m4 directory
ACLOCAL_AMFLAGS = -I m4 --install

AM_CXXFLAGS = -DDATADIR=\"$(abs_top_builddir)/data\"

# We have a binary program named chocan, and we list its sources
bin_PROGRAMS = chocan
chocan_SOURCES = src/main.cpp \
                 src/cac.cpp src/cac.h \
                 src/ServiceRecord.cpp src/ServiceRecord.h \
                 src/RecordManager.cpp src/RecordManager.h \
                 src/person.cpp src/person.h \
                 src/member.cpp src/member.h \
                 src/memberList.cpp src/memberList.h \
                 src/provider.cpp src/provider.h \
                 src/providerList.cpp src/providerList.h \
                 src/manager.cpp src/manager.h \
                 src/managerList.cpp src/managerList.h \
                 src/service.cpp src/service.h \
                 src/serviceList.cpp src/serviceList.h
dist_pkgdata_DATA = data/MemberDB.txt \
                    data/ProviderDB.txt \
                    data/ServiceDB.txt \
                    data/ManagerDB.txt \
                    data/RecordsDB.txt
# When new source files (.cpp or .h) are created, append them to the above
# list, separating with spaces.

check_PROGRAMS =

TESTS = $(check_PROGRAMS)
XFAIL_TESTS =
