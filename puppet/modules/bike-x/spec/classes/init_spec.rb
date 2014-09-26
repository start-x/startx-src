require 'spec_helper'
describe 'x' do

  context 'with defaults for all parameters' do
    it { should contain_class('x') }
  end
end
