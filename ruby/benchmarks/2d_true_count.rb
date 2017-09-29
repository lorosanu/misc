# encoding: utf-8

require 'benchmark'

header = 'Find out which 2D \'true\' count method is the fastest'
functions = {
  'each_count_method' => 'count=0; v.each{|sv| count += sv.count(true) }',
  'inject_count_method_v1' => 'v.inject(0){|sum, sv| sum + sv.count(true) }',
  'inject_count_method_v2' => 'v.inject(0){|sum, sv| sum + sv.count{|x| x } }',
  'each_each_if_method' => 'v.each{|sv| sv.each{|item| count += 1 if item } }',
  'times_times_if_method' => 'v.size.times{|i| v[i].size.times{|j| count += 1 if v[i][j] } }',
  'flatten_count_method' => 'v.flatten.count(true)',
}

def each_count_method(values)
  count = 0
  values.each{|items| count += items.count(true) }
  count
end

def inject_count_method_v1(values)
  values.inject(0){|sum, items| sum + items.count(true) }
end

def inject_count_method_v2(values)
  values.inject(0){|sum, items| sum + items.count{|x| x } }
end

def each_each_if_method(values)
  count = 0
  values.each{|items| items.each{|item| count += 1 if item } }
  count
end

def times_times_if_method(values)
  count = 0
  values.size.times{|i| values[i].size.times{|j| count += 1 if values[i][j] } }
  count
end

def flatten_count_method(values)
  values.flatten.count(true)
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
sizes = (1..3).map{|x| 10**x }

sizes.each do |n|
  matrix = [[false] * n] * n

  n.times do |i|
    n.times do |j|
      matrix[i][j] = [true, false].sample
    end
  end

  # check equal results
  check_equal_results(functions, matrix)

  # launch benchmark
  puts("\n\nMatrix=[#{n}, #{n}]\n\n")
  Benchmark.bmbm do |b|
    functions.each_key do |fname|
      b.report(fname){k.times{self.__send__(fname, matrix) } }
    end
  end
end

# => Performance order: each_count >~ inject_count_v1 >> inject_count_v2 > ...
