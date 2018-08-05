
class Animal
  def noise=noise
    @noise = noise
  end

  def noise
    @noise
  end
end

animal = Animal.new
animal.noise = "Moo!"
puts animal.noise

animal2 = Animal.new
animal2.noise = "Quack!"
puts animal2.noise
