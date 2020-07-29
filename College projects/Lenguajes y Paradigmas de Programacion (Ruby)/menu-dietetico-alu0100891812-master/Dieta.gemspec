# coding: utf-8
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'Dieta/version'

Gem::Specification.new do |spec|
  spec.name          = "Dieta"
  spec.version       = Dieta::VERSION
  spec.authors       = ["Rafael","Melissa"]
  spec.email         = ["alu0100891812@ull.edu.es","alu0100884012@ull.edu.es"]

  spec.summary       = %q{Practica 6. Haciendo una gema para una dieta.}
  spec.description   = %q{Mostrando un menú de dieta completo.}
  spec.homepage      = "https://github.com/ULL-ESIT-LPP-1617/tdd-menu-lpp-30"
  spec.license       = "MIT"

  # Prevent pushing this gem to RubyGems.org. To allow pushes either set the 'allowed_push_host'
  # to allow pushing to a single host or delete this section to allow pushing to any host.
  if spec.respond_to?(:metadata)
    spec.metadata['allowed_push_host'] = "http://mygemserver.com"
  else
    raise "RubyGems 2.0 or newer is required to protect against " \
      "public gem pushes."
  end

  spec.files         = `git ls-files -z`.split("\x0").reject do |f|
    f.match(%r{^(test|spec|features)/})
  end
  spec.bindir        = "exe"
  spec.executables   = spec.files.grep(%r{^exe/}) { |f| File.basename(f) }
  spec.require_paths = ["lib"]

  spec.add_development_dependency "bundler", "~> 1.13"
  spec.add_development_dependency "rake", ">= 12.3.3"
  spec.add_development_dependency "rspec", "~> 3.0"
  spec.add_development_dependency "guard"
  spec.add_development_dependency "guard-rspec"
  spec.add_development_dependency "guard-bundler"
  spec.add_development_dependency "rdoc", "~> 4.2"
end
