# encoding: utf-8

require 'benchmark'

header = 'Find out which sort in descending order is fastest'
functions = {
  'sort_reverse_method' => 'values.sort.reverse',
  'sort_reverse_each_method' => 'v= []; values.sort.reverse_each{|x| v << x }',
  'sort_by_method' => 'values.sort_by{|x| -x }',
  'sort_method' => 'values.sort{|x, y| y <=> x }',
}

def sort_reverse_method(values)
  values.sort.reverse
end

def sort_reverse_each_method(values)
  v = []
  values.sort.reverse_each{|x| v << x }
  v
end

def sort_by_method(values)
  values.sort_by{|x| -x }
end

def sort_method(values)
  values.sort{|x, y| y <=> x }
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
maxn = 1_000_000
sizes = (1..5).map{|x| 10**x }

sizes.each do |n|
  val = n.times.map{rand(maxn) }

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

# => v.sort.reverse
