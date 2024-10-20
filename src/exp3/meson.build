
exp3_caeser = executable('exp3_caeser', 'caeser.c')
exp3_substitution = executable('exp3_substitution', 'substitution.c')

hilldep = meson.get_compiler('c').find_library('m')

exp3_hill = executable('exp3_hill', 'hill.c', dependencies: hilldep)