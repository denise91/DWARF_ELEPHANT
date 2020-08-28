num_params_max = 50

print 'params.addRequiredParam<unsigned int>("num_online_solves","Number of online solves to perform");'
for i in range(num_params_max):
  print '    params.addParam<std::vector<Real>>("online_mu_'+str(i)+'",_zero_vect,"Online param value ' + str(i) + '");'

print " "

print "unsigned int _num_online_sovles;"

for i in range(num_params_max):
  print '    std::vector<Real> mu_'+str(i)+';'

print " "
num_params_actual = 3
params_actual = ['1.2e-3 2e-2 -0.1 -0.1 -0.1', '2.2e-3 3e-2 -0.1 -0.1 -0.1', '3.4e-3 5e-3 -0.1 -0.1 -0.1']

print '    num_online_solves = 3'
for i in range(num_params_actual):
  print '   mu_'+str(i)+"""= '""" + params_actual[i] + """ ' """
