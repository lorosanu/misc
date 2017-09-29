# encoding: utf-8

require 'benchmark'

header = 'Find out which euclidean method is the fastest'
functions = {
  'times_method' => 'a.size.times{|i| sum += (a[i] - b[i])**2 }',
  'each_index_method' => 'a.each_with_index{|a_i, i| sum += (a_i - b[i])**2 }',
  'zip_each_method' => 'a.zip(b).each{|a_i, b_i| sum += (a_i - b_i)**2 }',
  'zip_inject_method' => 'a.zip(b).inject(0){|sum, v| sum + (v[0] - v[1])**2 }',
  'zip_reduce_method' => 'a.zip(b).reduce(0){|sum, v| sum += (v[0]- v[1])**2 }',
}

def times_method(a, b)
  n = a.size

  sum = 0.0
  n.times{|i| sum += (a[i] - b[i])**2 }

  Math.sqrt(sum)
end

def each_index_method(a, b)
  sum = 0.0
  a.each_with_index{|a_i, i| sum += (a_i - b[i])**2 }

  Math.sqrt(sum)
end

def zip_each_method(a, b)
  sum = 0.0
  a.zip(b).each{|a_i, b_i| sum += (a_i - b_i)**2 }

  Math.sqrt(sum)
end

def zip_inject_method(a, b)
  Math.sqrt(a.zip(b).inject(0){|sum, v| sum + (v[0] - v[1])**2 })
end

def zip_reduce_method(a, b)
  Math.sqrt(a.zip(b).reduce(0){|sum, v| sum += (v[0] - v[1])**2 })
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

k = 10000
sizes = (1..4).map{|x| 10**x }

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

# => Performance order: times > each > zip_each > zip_inject > zip_reduce
