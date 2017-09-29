# encoding: utf-8

require 'benchmark'

header = 'Find out which index-min method is the fastest'
functions = {
  'index_min_method' => 'v.index(v.min)',
  'each_index_if_method' => 'v.each_with_index{|x, index| if x < min_val ... }',
  'each_index_min_method' => 'v.each_with_index.min[-1]',
}

def index_min_method(values)
  values.index(values.min)
end

def each_index_if_method(values)
  min_index = 0
  min_val = values[0]
  values.each_with_index do |x, index|
    if x < min_val
      min_val = x
      min_index = index
    end
  end
  min_index
end

def each_index_min_method(values)
  values.each_with_index.min[-1]
end

def check_equal_results(functions, values)
  res = []
  functions.each_key{|fname| res << self.__send__(fname, values) }

  raise "Functions generate different results: #{functions.keys.zip(res).to_h}"\
    unless res.uniq.size == 1
end

puts(header)
margin = functions.keys.map{|s| s.size }.max + 2
functions.each{|fname, desc| puts("#{fname.ljust(margin)} #{desc}") }

k = 1000
sizes = (1..5).map{|x| 10**x }

sizes.each do |n|
  val = n.times.map{rand() }

  # check equal results
  check_equal_results(functions, val)

  # launch benchmark
  puts("\n\nN=#{n}\n\n")
  Benchmark.bmbm do |b|
    functions.each_key do |fname|
      b.report(fname){k.times{self.__send__(fname, val) } }
    end
  end
end

# => Performance order: index_min >~ each_index_if >> each_index_min
