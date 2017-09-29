# encoding: utf-8

require 'benchmark'

header = 'Find out which map & sum method is the fastest'
functions = {
  'each_method' => 'v.each{|x| sum += Math.exp(x - max_value) }',
  'inject_method' => 'v.inject(0){|sum, x| sum + Math.exp(x - max_value) }',
  'map_inject_method' => 'v.map{|x| Math.exp(x - max_value) }.inject(0, :+)',
  'map_reduce_method' => 'v.map{|x| Math.exp(x - max_value) }.reduce(0, :+)',
}

def each_method(values, max_value)
  sum = 0
  values.each{|x| sum += Math.exp(x - max_value) }
  sum
end

def inject_method(values, max_value)
  values.inject(0){|sum, x| sum + Math.exp(x - max_value) }
end

def map_inject_method(values, max_value)
  values.map{|x| Math.exp(x - max_value) }.inject(0, :+)
end

def map_reduce_method(values, max_value)
  values.map{|x| Math.exp(x - max_value) }.reduce(0, :+)
end

def check_equal_results(functions, val, max_value)
  res = []
  functions.each_key{|fname| res << self.__send__(fname, val, max_value) }

  raise "Functions generate different results: #{functions.keys.zip(res).to_h}"\
    unless res.uniq.size == 1
end

puts(header)
margin = functions.keys.map{|s| s.size }.max + 2
functions.each{|fname, desc| puts("#{fname.ljust(margin)} #{desc}") }

k = 1000
max_value = 1.0
sizes = (1..5).map{|x| 10**x }

sizes.each do |n|
  val = n.times.map{rand() }

  # check equal results
  check_equal_results(functions, val, max_value)

  # launch benchmark
  puts("\n\nN=#{n}\n\n")
  Benchmark.bmbm do |b|
    functions.each_key do |fname|
      b.report(fname){k.times{self.__send__(fname, val, max_value) } }
    end
  end
end

# => Performance order:  each > inject > map_reduce >= map_inject
