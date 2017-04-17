require "tty-prompt"

class Phonebook
  attr_accessor :prompt, :phonebook
  def initialize
    @prompt = TTY::Prompt.new
    @phonebook = [
      { name: "Frank Sinatra",   number: "(626) 867 5309" },
      { name: "Dean Martin",     number: "(818) 253 4646" },
      { name: "Joey Bishop",     number: "(323) 640 3626" },
      { name: "Sammy Davis Jr.", number: "(914) 468 2413" },
      { name: "Peter Lawford",   number: "(253) 509 4292" },
    ]
  end

  def start
    print_intro

    option = ""
    options = ["Add Person to Phonebook", "Delete Person", "List Phonebook", "Quit"]

    while(option != "Quit")
      option = prompt.select("Please select an action to take", options)

      case option
      when options[0]
        add_person
      when options[1]
        delete_person
      when options[2]
        list_phonebook
      when options[3]
        break
      end
    end
  end

  def print_intro
    puts "=" * 80
    puts "=" * 22 + " Welcome to the Las Vegas Phonebook " + "=" * 22
    puts "=" * 80
    puts
  end

  def validate_number(number)
    !!number.match(/^\s*(?:\+?(\d{1,3}))?[-. (]*(\d{3})[-. )]*(\d{3})[-. ]*(\d{4})\s*$/)
  end

  def validate_name(name)
    !!name.match(/^[a-z ]+(,|-|\'){0,2}[a-z ]*(,| ){0,2}[a-z ]*(.)?$/i)
  end

  def list_phonebook
    puts
    phonebook.each do |person|
      puts "#{person[:name]} - #{person[:number]}"
    end
    puts
  end

  def add_person
    name = ""
    while !validate_name(name)
      name = prompt.ask("Name: ")
      if !validate_name(name)
        puts "Invalid Name"
      end
    end

    number = ""
    while !validate_number(number)
      number = prompt.ask("Phone Number: ")
      if !validate_number(number)
        puts "Invalid Phone Number"
      end
    end

    phonebook << { name: name, number: number }
    puts "#{name} - #{number} has been added to the phonebook"
    puts
  end

  def delete_person
    list_phonebook

    option = prompt.select("Delete Person by Name of Number?", %w(Name Number))

    case option
    when /Name/
      delete_person_by_name
    when /Number/
      delete_person_by_number
    end
  end

  def delete_person_by_name
    puts
    names = phonebook.map { |person| person[:name] }.join("|")
    str   = Regexp.escape(names).gsub(/\\\|/, "|")
    regex = Regexp.new("(#{ str })")

    name = ""
    while !regex.match(name)
      name = prompt.ask("Please enter the name of the person to be deleted: ")
    end
    @phonebook = @phonebook.select { |person| person[:name] != name }

    puts "#{name} has been deleted"
    puts
  end

  def delete_person_by_number
    puts
    numbers = phonebook.map { |person| person[:number] }.join("|")
    str     = Regexp.escape(numbers).gsub(/\\\|/, "|")
    regex   = Regexp.new("(#{ str })")

    number = ""
    while !regex.match(number)
      number = prompt.ask("Please enter the phone number of the person to be deleted: ")
    end

    deleted = @phonebook.select { |person| person[:number] == number }.first
    @phonebook = @phonebook.select { |person| person[:number] != number }

    puts "#{deleted[:name]} has been deleted"
    puts
  end
end

Phonebook.new.start

# FOR TESTING
#################################################################################
# book = Phonebook.new
# puts "Acceptable inputs"
# File.open("acceptable_names.txt").each do |line|
#   # remove newline character
#   line.gsub!(/\n/, '')

#   if !book.validate_name(line)
#     puts "#{line} is a violation"
#   end
# end

# puts
# puts "UNACCEPTABLE INPUTS"
# File.open("unacceptable_names.txt").each do |line|
#   # remove newline character
#   line.gsub!(/\n/, '')

#   if !book.validate_name(line)
#     puts "#{line} is a violation"
#   end
# end
