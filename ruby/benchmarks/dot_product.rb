# encoding: utf-8

require 'benchmark'
require 'matrix'
require 'narray'
require 'numo/narray'

header = 'Find out which dot-product method is fastest'
functions = {
  'while_method' => 'while i < size sum += a[i] * b[i], ... ',
  'zip_method' => 'sum = 0; a.zip(b){|x, y| sum += x * y }',
  'times_method' => 'sum = 0; a.size.times{|i| sum += a[i] * b[i] }',
  'narray_method1' => 'NVector.to_na(a) * NVector.to_na(b)',
  'narray_method2' => 'NVector[*a] * NVector[*b]',
  'numo_narray_method' => 'Numo::NArray[*a].dot(Numo::NArray[*b])',
  'inject_method' => '(0...a.size).inject(0){|r, i| r + a[i] * b[i] }',
  'vector_method' => 'Vector[*a].inner_product(Vector[*b])',
  'zip_inject_method' => 'a.zip(b).inject(0){|sum, els| sum + els[0] * els[1] }',
  'zip_map_inject_method' => 'a.zip(b).map{|x, y| x * y }.inject{|sum, el| sum + el }',
  'matrix_method' => '(Matrix.row_vector(a) * Matrix.column_vector(b)).element(0,0)',
}

def while_method(a, b)
  sum, i, m = 0, 0, a.size
  while i < m
    sum += a[i] * b[i]
    i += 1
  end

  sum
end

def zip_method(a, b)
  sum = 0
  a.zip(b){|x, y| sum += x * y }

  sum
end

def times_method(a, b)
  sum = 0
  a.size.times{|i| sum += a[i] * b[i] }

  sum
end

def inject_method(a, b)
  (0...a.size).inject(0){|r, i| r + a[i] * b[i] }
end

def zip_inject_method(a, b)
  a.zip(b).inject(0){|sum, els| sum + els[0] * els[1] }
end

def zip_map_inject_method(a, b)
  a.zip(b).map{|x, y| x * y }.inject{|sum, el| sum + el }
end

def matrix_method(a, b)
  (Matrix.row_vector(a) * Matrix.column_vector(b)).element(0,0)
end

def vector_method(a, b)
  Vector[*a].inner_product(Vector[*b])
end

def narray_method1(a, b)
  NVector.to_na(a) * NVector.to_na(b)
end

def narray_method2(a, b)
  NVector[*a] * NVector[*b]
end

def numo_narray_method(a, b)
  Numo::NArray[*a].dot(Numo::NArray[*b])
end

def check_equal_results(functions, a, b)
  res = []
  functions.each_key{|fname| res << self.__send__(fname, a, b) }

  raise "Functions generate different results: #{functions.keys.zip(res).to_h}"\
    unless res.uniq.size == 1
end

puts(header)
margin = functions.keys.map{|s| s.size }.max + 2
functions.each{|fname, desc| puts("#{fname.ljust(margin)} #{desc}") }

k = 1000
sizes = (1..5).map{|x| 10**x }

sizes.each do |n|
  v1 = n.times.map{rand() }
  v2 = n.times.map{rand() }

  # check equal results
  check_equal_results(functions, v1, v2)

  # launch benchmark
  puts("\n\nN=#{n}\n\n")
  Benchmark.bmbm do |b|
    functions.each_key do |fname|
      b.report(fname){k.times{self.__send__(fname, v1, v2) } }
    end
  end
end

puts("\n\nRetry with only one NArray initialization")

sizes.each do |n|
  v1 = n.times.map{rand() }
  v2 = n.times.map{rand() }

  # launch benchmark
  puts("\n\nN=#{n}\n\n")
  Benchmark.bmbm do |b|
    b.report('numo_narray_method with only one initialization') do
      nv1 = Numo::NArray[*v1]
      nv2 = Numo::NArray[*v2]
      k.times{nv1.dot(nv2) }
    end
    b.report('narray_method1 with only one initialization') do
      nv1 = NVector.to_na(v1)
      nv2 = NVector.to_na(v2)
      k.times{nv1 * nv2 }
    end
    b.report('narray_method2 with only one initialization') do
      nv1 = NVector[*v1]
      nv2 = NVector[*v2]
      k.times{nv1 * nv2 }
    end
  end
end

