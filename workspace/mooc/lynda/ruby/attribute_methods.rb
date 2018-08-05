
class Animal 
  attr_accessor :name
  attr_writer   :color
  attr_reader   :legs, :arms

  def noise=noise
    @noise = noise
  end

  def noise
    @noise
  end
end

animal1 = Animal.new
animal1.noise = "Moo!"
puts animal1.noise
animal1.name = "Ameya"
puts animal1.name
animal1.color = "Back"
puts animal1.color

animal2 = Animal.new
animal2.noise = "Quack!"
puts animal2.noise
