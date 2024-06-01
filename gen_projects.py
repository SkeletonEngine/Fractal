import subprocess, sys, platform

if "--update-submodules" in sys.argv or "-u" in sys.argv:
  subprocess.run(['git', 'submodule', 'update', '--init', '--remote', '--recursive'])

if platform.system() == 'Windows':
  subprocess.run(['cmake', '-B build/Windows'])

elif platform.system() == 'Darwin':
  subprocess.run(['cmake', '-B build/macOS', '-G Xcode'])
