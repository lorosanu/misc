# encoding: utf-8

require 'benchmark'

header = 'Find out which method returning the key of maximum value is fastest'
functions = {
  'key_max_method' => 'h.key(h.values.max)',
  'each_if_method' => 'h.each{|k, v| if v > max ... }',
  'max_by_method' => 'h.max_by{|k,v| v}[0]',
}

def key_max_method(h)
  h.key(h.values.max)
end

def each_if_method(h)
  key = h.keys[0]
  max = h.values[0]
  h.each do |k, v|
    if v > max
      max = v
      key = k
    end
  end

  key
end

def max_by_method(h)
  h.max_by{|k,v| v}[0]
end

def check_equal_results(functions, h)
  res = []
  functions.each_key{|fname| res << self.__send__(fname, h) }

  raise "Functions generate different results: #{functions.keys.zip(res).to_h}"\
    unless res.uniq.size == 1
end

puts(header)
margin = functions.keys.map{|s| s.size }.max + 2
functions.each{|fname, desc| puts("#{fname.ljust(margin)} #{desc}") }

k = 1000
sizes = (1..4).map{|x| 10**x }

sizes.each do |n|
  val = {}
  n.times do
    check = true
    while check
      x = rand(n)
      y = rand(n)

      unless val.key?(x) || val.value?(y)
        check = false
        val[x] = y
      end
    end
  end

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

# => Performance order: key_max >~ each_if > max_by
