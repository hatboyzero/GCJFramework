@echo off

rem set BOOST_LOG_VENDOR_DROP=https://boost-log.svn.sourceforge.net/svnroot/boost-log/tags/%BOOST_LOG_VERSION%
set BOOST_LOG_VENDOR_DROP=https://boost-log.svn.sourceforge.net/svnroot/boost-log/trunk/boost-log

svn export --force %BOOST_LOG_VENDOR_DROP% %BOOST_SRC%

@echo on