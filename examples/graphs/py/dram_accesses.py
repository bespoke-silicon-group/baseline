import pandas
import numpy
import sys

caches = 8
cores  = caches * 4

vcache_log = sys.argv[1]
vcache_data = pandas.read_csv(vcache_log)

def field_count(vcache_data, field, caches, cores):
    start_vcache_data = vcache_data[field][(cores-1)*caches : cores*caches]
    end_vcache_data   = vcache_data[field][(2*cores-1)*caches : 2*cores*caches]
    return (numpy.array(end_vcache_data) - numpy.array(start_vcache_data)).sum() 

ld_miss = field_count(vcache_data, 'ld_miss', caches, cores)
st_miss = field_count(vcache_data, 'st_miss', caches, cores)

print('total ld_miss = {}, total st_miss = {}'.format(ld_miss, st_miss))
