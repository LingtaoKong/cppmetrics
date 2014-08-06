cc_library(
    name = 'cppmetrics',
    srcs = [
        'src/snapshot.cpp',
        'src/random_generator.cpp',
        'src/reservoir.cpp',
        'src/uniform_reservoir.cpp',
        'src/meter.cpp',
        'src/metrics.cpp',
        'src/csvfile_reporter.cpp', 
        'src/metrics_timer.cpp',    
    ],
    incs = [
        './include',
        './src',
    ],

    deps = [
    '#rt',
    '//thirdparty/glog:glog',
    '//thirdparty/boost:filesystem',
    '//thirdparty/boost:system',
    '//thirdparty/boost:thread',
    '//thirdparty/boost:date_time',
    ],
    
    extra_cppflags = [
    '-Wno-non-virtual-dtor',
    ],
)
