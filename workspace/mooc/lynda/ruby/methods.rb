value = 7
def welcome(name = "World")
  puts "Hello #{name}!"
end

def add_sub(n1, n2)
  add = n1 + n2
  sub = n1 - n2
  return [add, sub]
end

fruits = ['apple', 'pear', 'banana', 'plum']

def longest_word(words=[])
 longest_word = words.inject do |memo,word|
	 memo.length > word.length ? memo : word
   end
  puts longest_word
end

def over_five?(value=nil)
	puts value.to_i > 5 ? 'Over 5' : 'Not Over 5'
end

welcome
welcome("Ameya")
welcome("Deswandikar")
welcome "Rahul"
result = add_sub(2, 2) 
puts result[0]
puts result[1]

add, sub = add_sub(3,1)
puts add
puts sub

longest_word(fruits)
longest_word
over_five?
